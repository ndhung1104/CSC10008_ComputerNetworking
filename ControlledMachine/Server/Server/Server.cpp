﻿//#include "stdafx.h"
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include "iostream"
//#include <fstream>
//
//using namespace std;
//
//#define bufferSize 1024
//
//int main() {
//	
//	cout << "======= W11 Sockets =======\n";
//	cout << "========= SERVER ==========\n";
//	cout << "=== Step 1 - Set up DLL ===\n\n";
//
//	SOCKET serverSocket, acceptSocket;
//	int port = 55555;
//	WSADATA wsaData;
//	int wsaerr;
//	WORD wVersionRequested = MAKEWORD(2, 2);
//	wsaerr = WSAStartup(wVersionRequested, &wsaData);
//	if (wsaerr != 0) {
//		cout << "The Winsock dll not found!" << endl;
//		return 0;
//	}
//	else {
//		cout << "The winsock dll found!" << endl;
//		cout << "the status: " << wsaData.szSystemStatus << endl;
//	}
//
//	cout << "\n=== Step 2 - Set up Server Socket ===\n\n";
//
//	serverSocket = INVALID_SOCKET;
//	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (serverSocket == INVALID_SOCKET) {
//		cout << "Error at socket(): " << WSAGetLastError() << endl;
//		WSACleanup();
//		return 0;
//	}
//	else cout << "socket() is OK!" << endl;
//
//	cout << "\n=== Step 3 - Bind Socket ===\n\n";
//
//	sockaddr_in service;
//	service.sin_family = AF_INET;
//	InetPton(AF_INET, L"127.0.0.1", &service.sin_addr.s_addr);
//	service.sin_port = htons(port);
//	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
//		cout << "bind() failed: " << WSAGetLastError() << endl;
//		closesocket(serverSocket);
//		WSACleanup();
//		return 0;
//	}
//	else cout << "bind() is OK!" << endl;
//
//	cout << "\n=== Step 4 - Initiate Listen ===\n\n";
//
//	if (listen(serverSocket, 1) == SOCKET_ERROR) cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
//	else cout << "listen() is OK, I'm waiting for connections..." << endl;
//
//	cout << "\n=== Step 5 - Accept Connection from Client ===\n\n";
//
//	acceptSocket = accept(serverSocket, NULL, NULL);
//	if (acceptSocket == INVALID_SOCKET) {
//		cout << "accept failed: " << WSAGetLastError() << endl;
//		WSACleanup();
//		return -1;
//	}
//	cout << "Accepted connection" << endl;
//
//	cout << "\n=== Step 6 - Chat to the Client ===\n\n";
//
//	char buffer[bufferSize];
//
//	int byteCount = recv(acceptSocket, buffer, bufferSize, 0);
//
//	if (byteCount > 0) {
//		cout << "Message received: " << buffer << endl;
//	}
//	else WSACleanup();
//
//	char confirmation[200] = "Message received";
//
//	byteCount = send(acceptSocket, confirmation, 200, 0);
//
//	if (byteCount > 0) {
//		cout << "Automated message sent to the Client." << endl;
//	}
//	else WSACleanup();
//
//	cout << "\n=== Step 7 - Send image file to client ===\n\n";
//
//	ifstream file1("image.jpg", ios::binary);
//	if (!file1.is_open()) {
//		cout << "Failed to open file\n";
//	}
//	else {
//		while (!file1.eof()) {
//			file1.read(buffer, bufferSize);
//			int bytes_read = file1.gcount();
//			send(acceptSocket, buffer, bytes_read, 0);
//		}
//	}
//	file1.close();
//
//	system("pause");
//
//	cout << "\n=== Step 8 - Send video file to client ===\n\n";
//
//	ifstream file("video.mp4", ios::binary);
//	if (!file.is_open()) {
//		cout << "Failed to open file\n";
//	}
//	else {
//		while (!file.eof()) {
//			file.read(buffer, bufferSize);
//			int bytes_read = file.gcount();
//			send(acceptSocket, buffer, bytes_read, 0);
//		}
//	}
//	file.close();
//	cout << "Video sent successfully\n";
//
//	cout << "\n=== Step 9 - Close Socket ===\n\n";
//
//	system("pause");
//	WSACleanup();
//
//
//	return 0;
//}


#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <fstream>
#include <chrono>
#include <thread>
#include<atomic>
#include<Utility.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define bufferSize 1024

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
    InetPton(AF_INET, "10.123.0.185", &service.sin_addr.s_addr);
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
        while (true) {
            // Nhận tin nhắn từ client
            byteCount = recv(serverSocket, buffer, bufferSize, 0);
            if (byteCount > 0) {
                // Đảm bảo chuỗi kết thúc đúng
                buffer[byteCount] = '\0';
                cout << "Message from client: " << buffer << endl;
                if (strcmp(buffer, "SHUTDOWN") == 0) computer.shutdown();
                else if (strcmp(buffer, "RESET") == 0) computer.reset();
                else if (strcmp(buffer, "LISTAPP") == 0) computer.listApp();
                else if (strcmp(buffer, "STARTAPP") == 0) computer.startApp();
                else if (strcmp(buffer, "STOPAPP") == 0) computer.stopApp();
                else if (strcmp(buffer, "LISTSERVICE") == 0) computer.listService();
                else if(strcmp(buffer, "STARTSERVICE") == 0) computer.startService();
                else if(strcmp(buffer, "STOPSERVICE") == 0) computer.stopService();
                else if (strcmp(buffer, "SCREENSHOT") == 0) computer.screenShot();
                else if (strcmp(buffer, "COPYFILE") == 0) computer.copyFile();
                else if (strcmp(buffer, "STARTWEBCAME") == 0) computer.startWebcame();
                else if (strcmp(buffer, "STOPWEBCAME") == 0) computer.stopWebcame();
                else if (strcmp(buffer, "KEYLOGGER") == 0) {
                    std::cout << "Starting keyboard input monitor...\n";
                    std::cout << "All keyboard input will be displayed in this window.\n";
                    std::cout << "This program runs with user awareness for input testing.\n";
                    std::cout << "Program will stop after 10 seconds or press ESC to exit.\n\n";

                    // Start monitoring thread
                    std::thread monitorThread(keylogger);
                    
                    // Create another thread to stop monitoring after 10 seconds
                    std::thread timerThread(stopAfterDelay, serverSocket);
                    // Wait for monitoring thread to finish
                    monitorThread.join();
                    
                    // Wait for timer thread to finish
                    timerThread.join();
                    running = true;

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
