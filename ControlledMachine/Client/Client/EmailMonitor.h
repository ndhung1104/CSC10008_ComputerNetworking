#pragma once
#include "GoogleOAuth.h"
#include "GmailAPI.h"
#include <set>
#include <map>
#include <functional>
#include <thread>
#include <iostream>
#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <fstream>
#include <string>
#include <sstream>
#include "GoogleDriveAPI.h"

class EmailMonitor {
private:
    GmailAPI gmail;
    const int email_check_interval;
    TokenResponse current_token;
    GoogleOAuth oauth;
    GoogleDriveAPI drive;

    std::set<std::string> whitelist;
    std::map<std::string, std::function<void(const email&, const SOCKET&)>> commandFunctions;
    void initializeWhiteList();
    void processEmails(std::vector<email>& receivedEmails, const std::vector<SOCKET>& socketVector);
    void sendMessage(std::string message, SOCKET clientSocket);
    bool findSocketByIP(const std::string& ipAddress, const std::vector<SOCKET>& socketVector, SOCKET& foundSocket);
public:
    EmailMonitor(const std::string& client_id,
                const std::string& client_secret,
                const std::string& redirect_uri,
                const std::string& refresh_token,
                const GoogleDriveAPI& drive,
                int check_interval = 60);
    void start(const std::vector<SOCKET>& socketVector);
    void refreshTokenIfNeeded();
};