//#include "stdafx.h"
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include "iostream"
//#include <fstream>
//using namespace std;
//
//#define bufferSize 1024
//
//int main() {
//
//	cout << "======= W11 Sockets =======\n";
//	cout << "========= CLIENT ==========\n";
//	cout << "=== Step 1 - Set up DLL ===\n\n";
//
//	SOCKET clientSocket;
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
//		cout << "The Winsock dll found!" << endl;
//		cout << "The status: " << wsaData.szSystemStatus << endl;
//	}
//
//	cout << "\n=== Step 2 - Set up Client Socket ===\n\n";
//
//	clientSocket = INVALID_SOCKET;
//	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (clientSocket == INVALID_SOCKET) {
//		cout << "Error at socket(): " << WSAGetLastError() << endl;
//		WSACleanup();
//		return 0;
//	}
//	else cout << "socket() is OK!" << endl;
//
//	cout << "\n=== Step 3 - Connect with Server ===\n\n";
//
//
//	sockaddr_in clientService;
//	clientService.sin_family = AF_INET;
//	InetPton(AF_INET, L"127.0.0.1", &clientService.sin_addr.s_addr);
//	clientService.sin_port = htons(port);
//	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
//		cout << "Client: connect() - Failed to conect." << endl;
//		WSACleanup();
//		return 0;
//	}
//	else {
//		cout << "Client: connect() is OK." << endl;
//		cout << "Client: Can start sending and receiving data..." << endl;
//	}
//
//	cout << "\n=== Step 4 - Chat to the Server ===\n\n";
//
//	char buffer[bufferSize];
//
//	cout << "Please enter a message to send to the Server: ";
//	cin.getline(buffer, 1024);
//
//	int byteCount = send(clientSocket, buffer, bufferSize, 0);
//
//	if (byteCount > 0) {
//		cout << "Message sent: " << buffer << endl;
//	}
//	else WSACleanup();
//
//	byteCount = recv(clientSocket, buffer, bufferSize, 0);
//
//	if (byteCount > 0) {
//		cout << "Message received: " << buffer << endl;
//	}
//	else WSACleanup();
//
//	cout << "\n=== Step 5 - Receive image file from server ===\n\n";
//
//	ofstream file("received_image.jpg", ios::binary);
//	if (!file.is_open()) {
//		cout << "Failed to create file\n";
//	}
//	else {
//		int bytes_received;
//		while ((bytes_received = recv(clientSocket, buffer, bufferSize, 0)) > 0) {
//			file.write(buffer, bytes_received);
//		}
//	}
//	file.close();
//	cout << "File received successfully\n";
//
//
//	cout << "\n=== Step 6 - Receive video file from server ===\n\n";
//
//	ofstream file1("received_video.mp4", ios::binary);
//	if (!file1.is_open()) {
//		cout << "Failed to create file\n";
//	}
//	else {
//		int bytes_received;
//		while ((bytes_received = recv(clientSocket, buffer, bufferSize, 0)) > 0) {
//			file1.write(buffer, bytes_received);
//		}
//	}
//	file1.close();
//	cout << "Video received successfully\n";
//
//	cout << "\n=== Step 7 - Close Socket ===\n\n";
//
//
//	system("pause");
//	WSACleanup();
//
//
//
//	return 0;
//}

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <fstream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define bufferSize 1024

void receiveFile(SOCKET clientSocket, const char* output_filename) {
    ofstream file(output_filename, ios::binary);
    if (!file.is_open()) {
        cout << "Failed to create file: " << output_filename << endl;
        return;
    }

    // Nhận kích thước tệp
    int file_size;
    recv(clientSocket, (char*)&file_size, sizeof(file_size), 0);

    // Nhận nội dung tệp
    char buffer[bufferSize];
    int bytes_received;
    int total_bytes_received = 0;

    while (total_bytes_received < file_size) {
        bytes_received = recv(clientSocket, buffer, bufferSize, 0);
        if (bytes_received <= 0) {
            break;  // Kết nối bị ngắt
        }
        file.write(buffer, bytes_received);
        total_bytes_received += bytes_received;
    }

    file.close();
    cout << "File " << output_filename << " received successfully\n";
}

int main() {

    cout << "======= W11 Sockets =======\n";
    cout << "========= CLIENT ==========\n";
    cout << "=== Step 1 - Set up DLL ===\n\n";

    SOCKET clientSocket;
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

    cout << "\n=== Step 2 - Set up Client Socket ===\n\n";

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else cout << "socket() is OK!" << endl;

    cout << "\n=== Step 3 - Connect with Server ===\n\n";

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, L"127.0.0.1", &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(port);

    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "Client: connect() - Failed to connect." << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "Client: connect() is OK." << endl;
        cout << "Client: Can start sending and receiving data..." << endl;
    }

    cout << "\n=== Step 4 - Chat with the Server ===\n\n";

    char buffer[bufferSize];
    string message;

    while (true) {
        // Nhập tin nhắn từ người dùng
        cout << "Enter message to send to server (type 'exit' to quit): ";
        getline(cin, message);  // Đọc toàn bộ dòng tin nhắn

        // Nếu người dùng nhập 'exit', kết thúc kết nối
        if (message == "exit") {
            break;
        }

        // Gửi tin nhắn tới server
        int byteCount = send(clientSocket, message.c_str(), message.size(), 0);

        if (byteCount > 0) {
            cout << "Message sent: " << message << endl;
        }
        else {
            cout << "Failed to send message." << endl;
            break;
        }
    }

    cout << "\n=== Step 5 - Close Socket ===\n\n";

    closesocket(clientSocket);
    WSACleanup();

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
