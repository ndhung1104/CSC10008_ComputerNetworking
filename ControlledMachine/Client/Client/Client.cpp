#include "EmailMonitor.h"
#include <mutex>
#include <queue>
#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE 1024

const std::string client_ip = "10.122.1.138";

const std::string client_id = "406151454730-q8sbba0gq585nojc2al4351s27ksog0g.apps.googleusercontent.com";
const std::string client_secret = "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";
const std::string redirect_uri = "urn:ietf:wg:oauth:2.0:oob";
const std::string refresh_token = "1//0eveAtgQ5MoimCgYIARAAGA4SNgF-L9Ir0EyLHNUOawAwkrhABeSuWxn35ReZ4BxS1gITNyOUBZareb5zNyU64yrTViEFZPLajQ"; //"1//0eIEkjQbra3JLCgYIARAAGA4SNgF-L9Irmy1vV95LbvzisbEF4aQMZYpIPU3H4-_lejLLIG43JVL0AlxE3QA6OLw4j0c_NkVfXA";
    
const std::string client_id_drive = "406151454730-tf8nb9n3aku685cdf9kebmnfm9mdnj0d.apps.googleusercontent.com";
const std::string client_secret_drive = "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";
const std::string redirect_uri_drive = "urn:ietf:wg:oauth:2.0:oob";
const std::string refresh_token_drive = "1//0eil6wzo5TCouCgYIARAAGA4SNgF-L9IrcbAuj5no4Yu9P8WNKaHjLIznp1MsLqh1jI-WGqEPBRFe6IkpRMArqDgNb7sul45ntg"; //4/1AVG7fiRaDYVTeSLweVkc9j3hhLiF-BfSQmICL2IFN9UHgjTIRFl6CdNeods    "1//0eIEkjQbra3JLCgYIARAAGA4SNgF-L9Irmy1vV95LbvzisbEF4aQMZYpIPU3H4-_lejLLIG43JVL0AlxE3QA6OLw4j0c_NkVfXA";


// void receiveFile(SOCKET clientSocket, const char* output_filename) {
//     ofstream file(output_filename, ios::binary);
//     if (!file.is_open()) {
//         cout << "Failed to create file: " << output_filename << endl;
//         return;
//     }

//     // Nhận kích thước tệp
//     int file_size;
//     recv(clientSocket, (char*)&file_size, sizeof(file_size), 0);

//     // Nhận nội dung tệp
//     char buffer[bufferSize];
//     int bytes_received;
//     int total_bytes_received = 0;

//     while (total_bytes_received < file_size) {
//         bytes_received = recv(clientSocket, buffer, bufferSize, 0);
//         if (bytes_received <= 0) {
//             break;  // Kết nối bị ngắt
//         }
//         file.write(buffer, bytes_received);
//         total_bytes_received += bytes_received;
//     }

//     file.close();
//     cout << "File " << output_filename << " received successfully\n";
// }

// Shared resources
// std::queue<Order> orderQueue;
std::mutex queueMutex;
std::mutex consoleMutex;
// std::condition_variable queueCondVar;
std::vector<SOCKET> socketVector;
bool emailRunning = true;
bool listeningRunning = true;
bool emailStopped = false;
bool listeningStopped = false;




// Function prototypes for other threads
void emailProcessingThread() // receive email and put order in queue
{
    GoogleDriveAPI drive(client_id_drive, client_secret_drive, redirect_uri_drive, refresh_token_drive);
    EmailMonitor monitor(client_id, client_secret, redirect_uri, refresh_token, drive);
    while (emailRunning)
    {
        // consoleMutex.lock();
        // std::cout << "Processing email...\n";
        // consoleMutex.unlock();
        monitor.start(socketVector);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    emailStopped = true;
}

void sendFile(SOCKET clientSocket, const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    // Get file size
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Send file info header: "SendFile: filename filesize"
    std::string filename = filePath.substr(filePath.find_last_of("/\\") + 1);
    std::string fileHeader = "SendFile: " + filename + " " + std::to_string(fileSize);
    send(clientSocket, fileHeader.c_str(), fileHeader.size(), 0);

    // Wait for confirmation from the receiver
    char ackBuffer[10];
    recv(clientSocket, ackBuffer, sizeof(ackBuffer), 0);

    // Send file contents in chunks
    char buffer[BUFFER_SIZE];
    std::streamsize totalSent = 0;
    while (file) {
        file.read(buffer, BUFFER_SIZE);
        std::streamsize bytesToSend = file.gcount();

        int bytesSent = 0;
        while (bytesSent < bytesToSend) {
            int sent = send(clientSocket, buffer + bytesSent, bytesToSend - bytesSent, 0);
            if (sent == SOCKET_ERROR) {
                std::cerr << "Error sending file." << std::endl;
                return;
            }
            bytesSent += sent;
        }
        totalSent += bytesSent;
    }

    // Send end-of-file signal
    std::string endSignal = "FileEnd";
    send(clientSocket, endSignal.c_str(), endSignal.size(), 0);

    file.close();
    std::cout << "File sent successfully. Total bytes sent: " << totalSent << std::endl;
}


void checkingForMessage(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE];

    // Receive initial file header
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesReceived <= 0) {
        std::cerr << "Error receiving file header or client disconnected." << std::endl;
        return;
    }
    buffer[bytesReceived] = '\0';
    std::string header(buffer);

    // Parse filename and file size from the header
    std::istringstream headerStream(header);
    std::string command, filename;
    std::streamsize fileSize;
    headerStream >> command >> filename >> fileSize;

    if (command != "SendFile:") {
        std::cerr << "Unexpected command: " << command << std::endl;
        return;
    }

    std::ofstream outputFile(filename, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    // Send acknowledgment to sender
    const char* ack = "ACK";
    send(clientSocket, ack, strlen(ack), 0);

    // Receive file contents
    std::streamsize totalReceived = 0;
    while (totalReceived < fileSize) {
        bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            std::cerr << "Error receiving file data or client disconnected." << std::endl;
            outputFile.close();
            return;
        }

        outputFile.write(buffer, bytesReceived);
        totalReceived += bytesReceived;
    }

    // Check for end-of-file signal
    bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    buffer[bytesReceived] = '\0';
    if (std::string(buffer) == "FileEnd") {
        std::cout << "File received successfully. Total bytes received: " << totalReceived << std::endl;
    } else {
        std::cerr << "File transfer ended unexpectedly." << std::endl;
    }

    outputFile.close();
    // GoogleDriveAPI drive(client_id_drive, client_secret_drive, redirect_uri_drive, refresh_token_drive);
    // drive.uploadFile(filename, )
}

void listeningClient(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE];

    while (listeningRunning) {
        checkingForMessage(clientSocket);
        // Receive data from client
        // int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        // if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
        //     consoleMutex.lock();
        //     std::cout << "Client disconnected or error occurred." << std::endl;
        //     consoleMutex.unlock();
        //     break;
        // }

        // // Process the received data (here we're just echoing it back)
        // buffer[bytesReceived] = '\0'; // Null-terminate received data
        // consoleMutex.lock();
        // std::cout << "Received from client: " << buffer << std::endl;
        // consoleMutex.unlock();
    }
    listeningStopped = true;
}


void listenerThread()
{
    std::cout << "======= W11 Sockets =======\n";
    std::cout << "========= SERVER ==========\n";
    std::cout << "=== Step 1 - Set up DLL ===\n\n";

    SOCKET clientSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        std::cout << "The Winsock dll not found!" << std::endl;
        return;
    }
    else {
        std::cout << "The Winsock dll found!" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    std::cout << "\n=== Step 2 - Set up Server Socket ===\n\n";

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }
    else std::cout << "socket() is OK!" << std::endl;

    std::cout << "\n=== Step 3 - Bind Socket ===\n\n";

    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, client_ip.c_str(), &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (bind(clientSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }
    else std::cout << "bind() is OK!" << std::endl;

    std::cout << "\n=== Step 4 - Initiate L0isten ===\n\n";

    if (listen(clientSocket, 1) == SOCKET_ERROR) {
        std::cout << "listen(): Error listening on socket " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }
    else {
        std::cout << "listen() is OK, I'm waiting for connections..." << std::endl;
    }

    std::vector<std::thread> clientThreads;

    while ((!listeningStopped) || (!emailStopped)) {
        std::cout << "\n=== Step 5 - Accept Connection from Client ===\n\n";

        SOCKET acceptSocket = accept(clientSocket, NULL, NULL);
        if (acceptSocket == INVALID_SOCKET) {
            std::cout << "accept failed: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }
        std::cout << "Accepted connection" << std::endl;

        socketVector.push_back(acceptSocket);
        clientThreads.emplace_back(listeningClient, acceptSocket);
    }

    for (auto& t : clientThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
    for (int i = 0; i < socketVector.size(); i++)
        closesocket(socketVector[i]); // Đóng kết nối với client

    closesocket(clientSocket);
    WSACleanup();
}


int main() {
    
    
    std::thread emailProcessing(emailProcessingThread);
    std::thread socketListening(listenerThread);   

    // Main thread waits for other threads to complete
    emailProcessing.join();
    socketListening.join();

    return 0;
}

//int main() {
//
//    cout << "======= W11 Sockets =======\n";
//    cout << "========= CLIENT ==========\n";
//    cout << "=== Step 1 - Set up DLL ===\n\n";
//
//    SOCKET clientSocket;
//    int port = 55555;
//    WSADATA wsaData;
//    int wsaerr;
//    WORD wVersionRequested = MAKEWORD(2, 2);
//    wsaerr = WSAStartup(wVersionRequested, &wsaData);
//    if (wsaerr != 0) {
//        cout << "The Winsock dll not found!" << endl;
//        return 0;
//    }
//    else {
//        cout << "The Winsock dll found!" << endl;
//        cout << "The status: " << wsaData.szSystemStatus << endl;
//    }
//
//    cout << "\n=== Step 2 - Set up Client Socket ===\n\n";
//
//    clientSocket = INVALID_SOCKET;
//    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    if (clientSocket == INVALID_SOCKET) {
//        cout << "Error at socket(): " << WSAGetLastError() << endl;
//        WSACleanup();
//        return 0;
//    }
//    else cout << "socket() is OK!" << endl;
//
//    cout << "\n=== Step 3 - Connect with Server ===\n\n";
//
//    sockaddr_in clientService;
//    clientService.sin_family = AF_INET;
//    InetPton(AF_INET, L"127.0.0.1", &clientService.sin_addr.s_addr);
//    clientService.sin_port = htons(port);
//    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
//        cout << "Client: connect() - Failed to connect." << endl;
//        WSACleanup();
//        return 0;
//    }
//    else {
//        cout << "Client: connect() is OK." << endl;
//        cout << "Client: Can start sending and receiving data..." << endl;
//    }
//
//    cout << "\n=== Step 4 - Chat to the Server ===\n\n";
//
//    char buffer[bufferSize];
//
//    cout << "Please enter a message to send to the Server: ";
//    cin.getline(buffer, 1024);
//
//    int byteCount = send(clientSocket, buffer, bufferSize, 0);
//
//    if (byteCount > 0) {
//        cout << "Message sent: " << buffer << endl;
//    }
//    else WSACleanup();
//
//    byteCount = recv(clientSocket, buffer, bufferSize, 0);
//
//    if (byteCount > 0) {
//        cout << "Message received: " << buffer << endl;
//    }
//    else WSACleanup();
//
//    cout << "\n=== Step 5 - Receive image file from server ===\n\n";
//    receiveFile(clientSocket, "received_image.jpg");
//
//    cout << "\n=== Step 6 - Receive video file from server ===\n\n";
//    receiveFile(clientSocket, "received_video.mp4");
//
//    cout << "\n=== Step 7 - Close Socket ===\n\n";
//
//    closesocket(clientSocket);
//    WSACleanup();
//
//    system("pause");
//    return 0;
//}
