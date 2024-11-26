#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 55555
#define BUFFER_SIZE 1024

std::vector<std::string> clientIPs; // Danh sách các địa chỉ IP client

void handleClient(SOCKET clientSocket) {
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
                        if (std::find(clientIPs.begin(), clientIPs.end(), ipAddress) == clientIPs.end()) {
                            clientIPs.push_back(ipAddress);
                        }
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

int main() {
    // Khởi động Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed winsock!" << std::endl;
        return 1;
    }

    // Tạo socket cho máy chủ
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Tạo socket thất bại!" << std::endl;
        WSACleanup();
        return 1;
    }

    // Thiết lập địa chỉ và cổng cho máy chủ
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Chấp nhận kết nối từ địa chỉ IP này
    serverAddr.sin_port = htons(PORT);

    // Liên kết socket với địa chỉ và cổng
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Liên kết socket thất bại!" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Lắng nghe kết nối đến
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Lắng nghe kết nối thất bại!" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Listening at the port " << PORT << "..." << std::endl;

    while (true) {
        // Chấp nhận kết nối từ client
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            handleClient(clientSocket); // Xử lý yêu cầu từ client
        }
    }

    // Dọn dẹp
    closesocket(serverSocket); // Đóng socket của máy chủ
    WSACleanup(); // Dọn dẹp Winsock
    return 0;
}
