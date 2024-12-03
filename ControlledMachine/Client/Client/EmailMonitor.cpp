#include "EmailMonitor.h"


#pragma comment(lib, "Ws2_32.lib")

#define bufferSize 1024

EmailMonitor::EmailMonitor(const std::string& client_id,
                         const std::string& client_secret,
                         const std::string& redirect_uri,
                         const std::string& refresh_token,
                         const GoogleDriveAPI& drive,
                         int check_interval)
    : oauth(client_id, client_secret, redirect_uri, refresh_token),
      gmail(oauth),
      email_check_interval(check_interval),
      drive(drive) {
    
    current_token = oauth.refreshAccessToken();
    if (!current_token.access_token.empty()) {
        std::cout << "Initial Access Token obtained." << std::endl;
    }
    else
        std::cout << "Empty." << std::endl;
}

void EmailMonitor::sendMessage(std::string message, SOCKET clientSocket)
{
    int byteCount = send(clientSocket, message.c_str(), message.size(), 0);

    if (byteCount > 0) {
        std::cout << "Message sent: " << message <<  std::endl;
    }
    else {
        std::cout << "Failed to send message." <<  std::endl;
    }
}

void EmailMonitor::initializeWhiteList()
{
    // Initialize whitelist
    whitelist = {"ndhung23@clc.fitus.edu.vn", "lpcuong23@clc.fitus.edu.vn"};
    
    // Initialize command functions
    commandFunctions = {
    {"SHUTDOWN", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n";
        sendMessage("SHUTDOWN", clientSocket);
    }},
    {"RESET", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
        sendMessage("RESET", clientSocket);
    }},
    {"STARTKEYLOGGER", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
        sendMessage("KEYLOGGER", clientSocket);
    }},
    {"STOPKEYLOGGER", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
        sendMessage("STOP", clientSocket);
    }},
    {"LISTAPP", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
        sendMessage("LISTAPP", clientSocket);
    }},
    {"STARTAPP", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
        std::istringstream stream(email.body);
        std::string firstLine;
        std::getline(stream, firstLine);
        trimEnd(firstLine);
        std::string secondLine;
        std::getline(stream, secondLine);
        std::getline(stream, secondLine);
        trimEnd(secondLine);
        secondLine = "STARTAPP " + secondLine;
        sendMessage(secondLine, clientSocket);
    }},
    {"STOPAPP", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        std::istringstream stream(email.body);
        std::string firstLine;
        std::getline(stream, firstLine);
        trimEnd(firstLine);
        std::string secondLine;
        std::getline(stream, secondLine);
        std::getline(stream, secondLine);
        trimEnd(secondLine);
        sendMessage("STOPAPP " + secondLine, clientSocket);
    }},
    {"LISTSERVICES", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        sendMessage("LISTSERVICES", clientSocket);
    }},
    {"STARTSERVICES", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        std::istringstream stream(email.body);
        std::string firstLine;
        std::getline(stream, firstLine);
        trimEnd(firstLine);
        std::string secondLine;
        std::getline(stream, secondLine);
        std::getline(stream, secondLine);
        trimEnd(secondLine);
        sendMessage("STARTSERVICES " + secondLine, clientSocket);
    }},
    {"STOPSERVICES", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        std::istringstream stream(email.body);
        std::string firstLine;
        std::getline(stream, firstLine);
        trimEnd(firstLine);
        std::string secondLine;
        std::getline(stream, secondLine);
        std::getline(stream, secondLine);
        trimEnd(secondLine);
        sendMessage("STOPSERVICES " + secondLine, clientSocket);
    }},
    {"COPYFILE", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        std::istringstream stream(email.body);
        std::string firstLine;
        std::getline(stream, firstLine);
        trimEnd(firstLine);
        std::string secondLine;
        std::getline(stream, secondLine);
        trimEnd(secondLine);
        sendMessage("COPYFILE " + secondLine, clientSocket);
    }},
    {"DELETEFILE", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        std::istringstream stream(email.body);
        std::string firstLine;
        std::getline(stream, firstLine);
        trimEnd(firstLine);
        std::string secondLine;
        std::getline(stream, secondLine);
        trimEnd(secondLine);
        sendMessage("DELETEFILE " + secondLine, clientSocket);
    }},
    {"SCREENSHOT", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        sendMessage("SCREENSHOT", clientSocket);
    }},
    {"STARTWEBCAM", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        sendMessage("STARTWEBCAM", clientSocket);
    }},
    {"STOPWEBCAM", [this](const email& email, const SOCKET& clientSocket) { 
        std::cout << "Executing Command 2\n"; 
        std::cout << "Email body: " << email.body << "\n";
        sendMessage("STOPWEBCAM", clientSocket);
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

void EmailMonitor::start(const std::vector<SOCKET>& socketVector, std::vector<email>& mailList) {
    refreshTokenIfNeeded();
    initializeWhiteList();
    gmail.getEmailList(current_token.access_token);

    if (gmail.receivedEmail.size() > 0)
    {
        for (int i = 0; i < gmail.receivedEmail.size(); i++)
            mailList.push_back(gmail.receivedEmail[i]);
        processEmails(gmail.receivedEmail, socketVector);
    }
    
}

    // std::cout << "======= W11 Sockets =======\n";
    // std::cout << "========= SERVER ==========\n";
    // std::cout << "=== Step 1 - Set up DLL ===\n\n";

    // SOCKET clientSocket, acceptSocket;
    // int port = 55555;
    // WSADATA wsaData;
    // int wsaerr;
    // WORD wVersionRequested = MAKEWORD(2, 2);
    // wsaerr = WSAStartup(wVersionRequested, &wsaData);
    // if (wsaerr != 0) {
    //     std::cout << "The Winsock dll not found!" << std::endl;
    //     return;
    // }
    // else {
    //     std::cout << "The Winsock dll found!" << std::endl;
    //     std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    // }

    // std::cout << "\n=== Step 2 - Set up Server Socket ===\n\n";

    // clientSocket = INVALID_SOCKET;
    // clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // if (clientSocket == INVALID_SOCKET) {
    //     std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
    //     WSACleanup();
    //     return;
    // }
    // else std::cout << "socket() is OK!" << std::endl;

    // std::cout << "\n=== Step 3 - Bind Socket ===\n\n";

    // sockaddr_in service;
    // service.sin_family = AF_INET;
    // InetPton(AF_INET, "10.123.0.185", &service.sin_addr.s_addr);
    // service.sin_port = htons(port);
    // if (bind(clientSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
    //     std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
    //     closesocket(clientSocket);
    //     WSACleanup();
    //     return;
    // }
    // else std::cout << "bind() is OK!" << std::endl;

    // std::cout << "\n=== Step 4 - Initiate L0isten ===\n\n";

    // if (listen(clientSocket, 1) == SOCKET_ERROR) {
    //     std::cout << "listen(): Error listening on socket " << WSAGetLastError() << std::endl;
    //     WSACleanup();
    //     return;
    // }
    // else {
    //     std::cout << "listen() is OK, I'm waiting for connections..." << std::endl;
    // }

    // while (true) {
    //     std::cout << "\n=== Step 5 - Accept Connection from Client ===\n\n";

    //     acceptSocket = accept(clientSocket, NULL, NULL);
    //     if (acceptSocket == INVALID_SOCKET) {
    //         std::cout << "accept failed: " << WSAGetLastError() << std::endl;
    //         WSACleanup();
    //         return;
    //     }
    //     std::cout << "Accepted connection" << std::endl;

    //     std::cout << "\n=== Step 6 - Receive Message from Client ===\n\n";

    //     char buffer[bufferSize];
    //     int byteCount;
    //     initializeWhiteList(acceptSocket);
    //     while (true) {
    //         // Nhận tin nhắn từ client
    //         sendMessage("Sending", acceptSocket);
    //         refreshTokenIfNeeded();
    //         gmail.getEmailList(current_token.access_token);

    //         if (gmail.receivedEmail.size() > 0)
    //         {
    //             std::cout << "New " << gmail.receivedEmail.size() << " mail!\n";
    //             processEmails(gmail.receivedEmail);
    //         }
    //         else 
    //             std::cout << "No new mail!\n";
    //         std::this_thread::sleep_for(std::chrono::seconds(10));
    //         }

    //         closesocket(acceptSocket); // Đóng kết nối với client
    // }

    // closesocket(clientSocket);
    // WSACleanup();

    
    // gmail.sendEmail(current_token.access_token, "ndhung23@clc.fitus.edu.vn", "ABCXYZ", "lalalalala");
// }
void EmailMonitor::trimEnd(std::string &str) {
    while (!str.empty() && (str.back() == '\r' || str.back() == '\n')) {
        str.pop_back();
    }
}

bool EmailMonitor::findSocketByIP(std::string ipAddress, const std::vector<SOCKET>& socketVector, SOCKET& foundSocket) {
    struct sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);

    for (const SOCKET& socket : socketVector) {
        // Get the peer (remote) address of the socket
        if (getpeername(socket, (struct sockaddr*)&addr, &addrLen) == 0) {
            char socketIP[INET_ADDRSTRLEN];

            // Convert the IP address from binary to text form
            inet_ntop(AF_INET, &addr.sin_addr, socketIP, INET_ADDRSTRLEN);
            std::string socketIPString(socketIP);
            // std::cout << "Ip address: " << ipAddress << std::endl << "Socket IP address: " << socketIPString << std::endl;
            // Compare the socket's IP address with the target IP address
            // std::cout << "ipAddress length: " << ipAddress.length() << ", socketIPString length: " << socketIPString.length() << std::endl;
            // for (size_t i = 0; i < ipAddress.size(); ++i) {
            //     std::cout << "ipAddress[" << i << "] = " << (int)ipAddress[i] << ", socketIPString[" << i << "] = " << (int)socketIPString[i] << std::endl;
            // }
            if (ipAddress.compare(socketIPString) == 0) {
                foundSocket = socket; // Assign the matching socket to foundSocket
                // std::cout << "Found socket!";
                return true;           // Socket with matching IP found
            }
        }
        // std::cout << ipAddress << std::endl;
    }

    return false; // No matching socket found
}


void EmailMonitor::processEmails(std::vector<email>& receivedEmails, const std::vector<SOCKET>& socketVector)
{
    auto it = receivedEmails.begin();
    while (it != receivedEmails.end()) {
        if (whitelist.count(it->sender)) {
            auto command = commandFunctions.find(it->subject);
            if (command != commandFunctions.end()) {
                // std::cout << "Processing email from: " << it->sender << " with command: " << it->subject << "\n";
                std::istringstream stream(it->body);
                std::string firstLine;
                std::getline(stream, firstLine);
                trimEnd(firstLine);
                // std::cout << it->body << std::endl;
                // std::cout << firstLine << std::endl;
                SOCKET targetSocket;
                if (findSocketByIP(firstLine, socketVector, targetSocket))
                    command->second(*it, targetSocket); // Execute the function associated with the subject command
            }
        }
        it = receivedEmails.erase(it); // Remove the processed email and update the iterator
    }
}