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


class EmailMonitor {
private:
    GmailAPI gmail;
    const int email_check_interval;
    TokenResponse current_token;
    GoogleOAuth oauth;
    
    std::set<std::string> whitelist;
    std::map<std::string, std::function<void(const email&)>> commandFunctions;
    void initializeWhiteList(SOCKET clientSocket);
    void processEmails(std::vector<email>& receivedEmails);
    void sendMessage(std::string message, SOCKET clientSocket);
public:
    EmailMonitor(const std::string& client_id,
                const std::string& client_secret,
                const std::string& redirect_uri,
                const std::string& refresh_token,
                int check_interval = 60);
    void start();
    void refreshTokenIfNeeded();
};