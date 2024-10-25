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
}