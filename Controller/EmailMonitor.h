#pragma once
#include "GoogleOAuth.h"
#include "GmailAPI.h"

class EmailMonitor {
private:
    
    GmailAPI gmail;
    const int email_check_interval;
    TokenResponse current_token;

public:
    GoogleOAuth oauth;
    EmailMonitor(const std::string& client_id,
                const std::string& client_secret,
                const std::string& redirect_uri,
                const std::string& refresh_token,
                int check_interval = 60);

    void start();
    void refreshTokenIfNeeded();
};