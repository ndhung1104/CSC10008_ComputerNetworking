#pragma once
#include <string>
#include "GoogleOAuth.h"
#include <vector>

struct email
{
    std::string sender, subject, body;
    long long internalDate;
};

class GmailAPI {
private:
    GoogleOAuth& oauth;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::string decodeBase64(const std::string& encoded_str);
    std::string extractEmail(const std::string& fullSender);
public:
    std::vector<email> receivedEmail;
    explicit GmailAPI(GoogleOAuth& oauth);
    void getEmailDetails(const std::string& access_token, const std::string& message_id);
    void getEmailList(const std::string& access_token, const std::string& query = "is:unread");
    bool markAsRead(const std::string& access_token, const std::string& message_id);
};