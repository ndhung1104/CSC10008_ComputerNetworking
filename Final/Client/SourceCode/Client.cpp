// g++ Client.cpp jsoncpp.cpp EmailMonitor.cpp GmailAPI.cpp GoogleDriveAPI.cpp GoogleOAuth.cpp -o client -I".\lib\curl\include" -L".\lib\curl\lib" -lcurl -lws2_32
#include "UI.h"
#include "EmailMonitor.h"
#include <mutex>
#include <queue>
#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE 1024

// const std::string client_ip = "127.0.0.1";

const std::string client_id = "406151454730-q8sbba0gq585nojc2al4351s27ksog0g.apps.googleusercontent.com";
const std::string client_secret = "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";
const std::string redirect_uri = "urn:ietf:wg:oauth:2.0:oob";
// const std::string refresh_token = "1//0eveAtgQ5MoimCgYIARAAGA4SNgF-L9Ir0EyLHNUOawAwkrhABeSuWxn35ReZ4BxS1gITNyOUBZareb5zNyU64yrTViEFZPLajQ"; //"1//0eIEkjQbra3JLCgYIARAAGA4SNgF-L9Irmy1vV95LbvzisbEF4aQMZYpIPU3H4-_lejLLIG43JVL0AlxE3QA6OLw4j0c_NkVfXA";
    
const std::string client_id_drive = "406151454730-tf8nb9n3aku685cdf9kebmnfm9mdnj0d.apps.googleusercontent.com";
const std::string client_secret_drive = "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";
const std::string redirect_uri_drive = "urn:ietf:wg:oauth:2.0:oob";
// const std::string refresh_token_drive = "1//0eil6wzo5TCouCgYIARAAGA4SNgF-L9IrcbAuj5no4Yu9P8WNKaHjLIznp1MsLqh1jI-WGqEPBRFe6IkpRMArqDgNb7sul45ntg"; //4/1AVG7fiRaDYVTeSLweVkc9j3hhLiF-BfSQmICL2IFN9UHgjTIRFl6CdNeods    "1//0eIEkjQbra3JLCgYIARAAGA4SNgF-L9Irmy1vV95LbvzisbEF4aQMZYpIPU3H4-_lejLLIG43JVL0AlxE3QA6OLw4j0c_NkVfXA";

std::string client_ip, refresh_token, refresh_token_drive; //4/1AVG7fiRaDYVTeSLweVkc9j3hhLiF-BfSQmICL2IFN9UHgjTIRFl6CdNeods    "1//0eIEkjQbra3JLCgYIARAAGA4SNgF-L9Irmy1vV95LbvzisbEF4aQMZYpIPU3H4-_lejLLIG43JVL0AlxE3QA6OLw4j0c_NkVfXA";

void initializeParameters()
{
    std::ifstream ifs("parameters.txt");
    getline(ifs, client_ip);
    getline(ifs, refresh_token);
    getline(ifs, refresh_token_drive);
    std::cout << client_ip << " " << client_ip.size() << "\n" << refresh_token << " " << refresh_token.size() << "\n" << refresh_token_drive << " " << refresh_token_drive.size() << " \n";
    ifs.close();
}

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
void emailProcessingThread(std::vector<email>& mailList) // receive email and put order in queue
{
    GoogleDriveAPI drive(client_id_drive, client_secret_drive, redirect_uri_drive, refresh_token_drive);
    EmailMonitor monitor(client_id, client_secret, redirect_uri, refresh_token, drive);
    while (emailRunning)
    {
        // consoleMutex.lock();
        // std::cout << "Processing email...\n";
        // consoleMutex.unlock();
        monitor.start(socketVector, mailList);
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

// void checkingForMessage(SOCKET clientSocket) {
//     char buffer[BUFFER_SIZE];

//     // Receive initial file header
//     int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//     if (bytesReceived <= 0) {
//         // std::cerr << "Error receiving file header or client disconnected." << std::endl;
//         return;
//     }
//     buffer[bytesReceived] = '\0';
//     std::string header(buffer);

//     // Parse filename and file size from the header
//     std::istringstream headerStream(header);
//     std::string command, filename;
//     std::streamsize fileSize;
//     headerStream >> command >> filename >> fileSize;

//     if (command != "SendFile:") {
//         std::cerr << "Unexpected command: " << command << std::endl;
//         return;
//     }

//     std::ofstream outputFile(filename, std::ios::binary);
//     if (!outputFile.is_open()) {
//         std::cerr << "Failed to open file for writing." << std::endl;
//         return;
//     }

//     // Send acknowledgment to sender
//     const char* ack = "ACK";
//     send(clientSocket, ack, strlen(ack), 0);

//     // Receive file contents
//     std::streamsize totalReceived = 0;
//     while (totalReceived < fileSize) {
//         bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//         if (bytesReceived <= 0) {
//             std::cerr << "Error receiving file data or client disconnected." << std::endl;
//             outputFile.close();
//             return;
//         }

//         outputFile.write(buffer, bytesReceived);
//         totalReceived += bytesReceived;
//     }

//     // Check for end-of-file signal
//     bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
//     buffer[bytesReceived] = '\0';
//     if (std::string(buffer) == "FileEnd") {
//         std::cout << "File received successfully. Total bytes received: " << totalReceived << std::endl;
//     } else {
//         std::cerr << "File transfer ended unexpectedly." << std::endl;
//     }

//     outputFile.close();
//     std::vector<std::string> whitelist = {"ndhung23@clc.fitus.edu.vn", "lpcuong23@clc.fitus.edu.vn"};
//     std::cout << "1";
//     GoogleDriveAPI drive(client_id_drive, client_secret_drive, redirect_uri_drive, refresh_token_drive);
//     std::cout << "1";
//     drive.uploadFile(filename, filename, whitelist);
//     std::cout << "1";
// }

void checkingForMessage(SOCKET clientSocket) {
    try {
        char buffer[BUFFER_SIZE];
        
        // Set socket timeout
        int timeout = 5000; // 5 seconds
        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

        // Receive file header
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            throw std::runtime_error("Failed to receive file header");
        }
        buffer[bytesReceived] = '\0';

        // Parse header
        std::istringstream headerStream(buffer);
        std::string command, filename;
        std::streamsize fileSize;
        headerStream >> command >> filename >> fileSize;

        if (command != "SendFile:") {
            throw std::runtime_error("Invalid file transfer command");
        }

        std::cout << "Receiving file: " << filename 
                  << ", Size: " << fileSize << " bytes" << std::endl;

        // Open output file
        std::ofstream outputFile(filename, std::ios::binary);
        if (!outputFile) {
            throw std::runtime_error("Cannot open file for writing");
        }

        // Send acknowledgment
        send(clientSocket, "ACK", 3, 0);

        // Receive file contents
        std::streamsize totalReceived = 0;
        while (totalReceived < fileSize) {
            std::streamsize bytesRemaining = fileSize - totalReceived;
            int bytesToReceive = std::min(bytesRemaining, (std::streamsize)BUFFER_SIZE);
            
            bytesReceived = recv(clientSocket, buffer, bytesToReceive, 0);
            if (bytesReceived <= 0) {
                throw std::runtime_error("File receive error");
            }

            outputFile.write(buffer, bytesReceived);
            totalReceived += bytesReceived;

            std::cout << "Received: " << totalReceived 
                      << " / " << fileSize << " bytes" << std::endl;
        }

        // Verify end of file
        bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        buffer[bytesReceived] = '\0';
        if (std::string(buffer) != "FileEnd") {
            throw std::runtime_error("Incomplete file transfer");
        }

        std::cout << "File transfer complete: " << filename << std::endl;
        outputFile.close();
        std::vector<std::string> whitelist = {"ndhung23@clc.fitus.edu.vn", "lpcuong23@clc.fitus.edu.vn"};
        std::cout << "1";
        GoogleDriveAPI drive(client_id_drive, client_secret_drive, redirect_uri_drive, refresh_token_drive);
        std::cout << "1";
        drive.uploadFile(filename, filename, whitelist);
    }
    catch (const std::exception& e) {
        std::cerr << "File transfer error: " << e.what() << std::endl;
    }
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

void handleClient(SOCKET clientSocket, std::vector<std::string>& clientIPs) {
    char buffer[BUFFER_SIZE];
    int byteCount = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    
    if (byteCount > 0) {
        buffer[byteCount] = '\0'; // Kết thúc chuỗi
        std::string request(buffer);
        
        // Kiểm tra yêu cầu OPTIONS
        if (request.find("OPTIONS") == 0) {
            std::string response = "HTTP/1.1 204 No Content\r\n"
                                   "Access-Control-Allow-Origin: http://127.0.0.1:5502\r\n"
                                   "Access-Control-Allow-Methods: POST, OPTIONS\r\n"
                                   "Access-Control-Allow-Headers: content-type\r\n"
                                   "Content-Length: 0\r\n"
                                   "\r\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        }
        // Kiểm tra yêu cầu POST
        else if (request.find("POST") == 0) {
            size_t pos = request.find("Content-Length: ");
            if (pos != std::string::npos) {
                pos += 16; // Độ dài của "Content-Length: "
                size_t endPos = request.find("\r\n", pos);
                int contentLength = std::stoi(request.substr(pos, endPos - pos));
                
                // Đọc thông điệp
                std::string message(request.substr(request.find("\r\n\r\n") + 4, contentLength));
                std::string ipAddress = ""; // Biến để lưu địa chỉ IP
                
                // Tìm địa chỉ IP trong JSON
                size_t ipPos = message.find("\"ip\": \"");
                if (ipPos != std::string::npos) {
                    ipPos += 8; // Độ dài của "\"ip\": \""
                    size_t ipEnd = message.find("\"", ipPos);
                    if (ipEnd != std::string::npos) {
                        ipAddress = message.substr(ipPos, ipEnd - ipPos);
                        // Thêm IP vào danh sách
                        bool found = 0;
                        for (int i = 0; i < clientIPs.size(); i++)
                            if (clientIPs[i] == ipAddress)
                                found = 1;
                        if (found == 0)
                            clientIPs.push_back(std::string(ipAddress));
                        // if (std::find(clientIPs.begin(), clientIPs.end(), std::string(ipAddress)) == clientIPs.end()) {
                        //     clientIPs.push_back(std::string(ipAddress));
                        // }
                    }
                }
                
                // In thông điệp và địa chỉ IP
                std::cout << "Message: " << message << ", IP: " << ipAddress << std::endl;

                // Gửi phản hồi cho yêu cầu POST
                std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nThông điệp đã nhận";
                send(clientSocket, response.c_str(), response.size(), 0);
            }
        }
    }

    closesocket(clientSocket); // Đóng kết nối với client
}

void uiRunning(const std::vector<email>& mailList)
{
    UI ui(mailList, socketVector, client_ip);      // Khởi tạo đối tượng UI
    ui.run();   // Chạy giao diện người dùng
}


int main() {
    std::vector<email> mailList;
    std::vector<std::string> clientList;
    initializeParameters();

    std::thread uiThread(uiRunning, std::ref(mailList));
    std::thread emailProcessing(emailProcessingThread, std::ref(mailList));
    std::thread socketListening(listenerThread);   

    // Main thread waits for other threads to complete
    emailProcessing.join();
    socketListening.join();
    uiThread.join();

    return 0;
}
