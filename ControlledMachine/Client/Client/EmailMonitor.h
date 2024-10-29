#pragma once
#include "GoogleOAuth.h"
#include "GmailAPI.h"
#include <set>
#include <map>
#include <functional>

class EmailMonitor {
private:
    GmailAPI gmail;
    const int email_check_interval;
    TokenResponse current_token;
    GoogleOAuth oauth;

    std::set<std::string> whitelist;
    std::map<std::string, std::function<void(const email&)>> commandFunctions;
    void initializeWhiteList();
    void processEmails(std::vector<email>& receivedEmails);
public:
    EmailMonitor(const std::string& client_id,
                const std::string& client_secret,
                const std::string& redirect_uri,
                const std::string& refresh_token,
                int check_interval = 60);
    void start();
    void refreshTokenIfNeeded();
};