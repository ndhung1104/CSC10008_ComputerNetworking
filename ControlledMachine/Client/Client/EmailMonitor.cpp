#include "EmailMonitor.h"
#include <thread>
#include <iostream>

EmailMonitor::EmailMonitor(const std::string& client_id,
                         const std::string& client_secret,
                         const std::string& redirect_uri,
                         const std::string& refresh_token,
                         int check_interval)
    : oauth(client_id, client_secret, redirect_uri, refresh_token),
      gmail(oauth),
      email_check_interval(check_interval) {
    
    current_token = oauth.refreshAccessToken();
    if (!current_token.access_token.empty()) {
        std::cout << "Initial Access Token obtained." << std::endl;
    }

    initializeWhiteList();
}

void EmailMonitor::initializeWhiteList()
{
    // Initialize whitelist
    whitelist = {"ndhung23@clc.fitus.edu.vn", "lpcuong23@clc.fitus.edu.vn"};
    
    // Initialize command functions
    commandFunctions = {
    {"SHUTDOWN", [](const email& email) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
    }},
    {"RESET", [](const email& email) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
    }},
    {"KEYLOGGER", [](const email& email) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
    }},
    {"LISTAPP", [](const email& email) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
    }},
    {"STARTAPP", [](const email& email) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
    }},
    {"STOPAPP", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }},
    {"LISTSERVICES", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }},
    {"STARTSERVICES", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }},
    {"STOPSERVICES", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }},
    {"COPYFILE", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }},
    {"REMOVEFILE", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }},
    {"SCREENSHOT", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }},
    {"STARTWEBCAM", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }},
    {"STOPWEBCAM", [](const email& email) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
    }}
};
}

void EmailMonitor::refreshTokenIfNeeded() {
    if (oauth.isTokenExpired()) {
        current_token = oauth.refreshAccessToken();
        if (!current_token.access_token.empty()) {
            std::cout << "Token refreshed successfully." << std::endl;
        }
    }
}

void EmailMonitor::start() {
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
    InetPton(AF_INET, "10.122.4.92", &clientService.sin_addr.s_addr);
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
    
    refreshTokenIfNeeded();
    gmail.getEmailList(current_token.access_token);

    if (gmail.receivedEmail.size() > 0)
    {
        std::cout << "New " << gmail.receivedEmail.size() << " mail!\n";
        processEmails(gmail.receivedEmail);
    }
    else 
        std::cout << "No new mail!\n";
    // gmail.sendEmail(current_token.access_token, "ndhung23@clc.fitus.edu.vn", "ABCXYZ", "lalalalala");
}

void EmailMonitor::processEmails(std::vector<email>& receivedEmails)
{
    auto it = receivedEmails.begin();
    while (it != receivedEmails.end()) {
        if (whitelist.count(it->sender)) {
            auto command = commandFunctions.find(it->subject);
            if (command != commandFunctions.end()) {
                std::cout << "Processing email from: " << it->sender << " with command: " << it->subject << "\n";
                command->second(*it); // Execute the function associated with the subject command
            }
        }
        it = receivedEmails.erase(it); // Remove the processed email and update the iterator
    }
}