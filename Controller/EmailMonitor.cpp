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
    {"COMMAND_1", [](const email& email) { 
        std::cout << "Executing Command 1\n";
        std::cout << "Email body: " << email.body << "\n"; 
    }},
    {"COMMAND_2", [](const email& email) { 
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
    refreshTokenIfNeeded();
    gmail.getEmailList(current_token.access_token);

    if (gmail.receivedEmail.size() > 0)
    {
        std::cout << "New " << gmail.receivedEmail.size() << " mail!\n";
        processEmails(gmail.receivedEmail);
    }
    else 
        std::cout << "No new mail!\n";
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