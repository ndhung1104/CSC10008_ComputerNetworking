#pragma once
#include <string>
#include <tuple>
#include <chrono>

struct TokenResponse {
    std::string access_token;
    int expires_in;
};

class GoogleOAuth {
private:
    std::string client_id;
    std::string client_secret;
    std::string redirect_uri;
    std::string refresh_token;
    std::chrono::system_clock::time_point token_expiry_time;
    const int buffer_time = 10;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::tuple<std::string, std::string, int> extractTokens(const std::string& response);

public:
    GoogleOAuth(const std::string& client_id, 
                const std::string& client_secret, 
                const std::string& redirect_uri,
                const std::string& refresh_token);

    std::tuple<std::string, std::string, int> getAccessToken(const std::string& auth_code);
    TokenResponse refreshAccessToken();
    bool isTokenExpired() const;
    void updateExpiryTime(int expires_in);
};