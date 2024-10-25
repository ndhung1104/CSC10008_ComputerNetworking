// GoogleOAuth.cpp
#include "GoogleOAuth.h"
#include <curl/curl.h>
#include "json/json.h"
#include <sstream>
#include <iostream>

GoogleOAuth::GoogleOAuth(const std::string& client_id,
                        const std::string& client_secret,
                        const std::string& redirect_uri,
                        const std::string& refresh_token)
    : client_id(client_id),
      client_secret(client_secret),
      redirect_uri(redirect_uri),
      refresh_token(refresh_token) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

size_t GoogleOAuth::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::tuple<std::string, std::string, int> GoogleOAuth::extractTokens(const std::string& response) {
    Json::CharReaderBuilder builder;
    Json::Value jsonData;
    std::string errs;
    std::istringstream s(response);
    
    std::string access_token, refresh_token;
    int expires_in = 0;
    
    if (Json::parseFromStream(builder, s, &jsonData, &errs)) {
        if (jsonData.isMember("access_token")) {
            access_token = jsonData["access_token"].asString();
        }
        if (jsonData.isMember("refresh_token")) {
            refresh_token = jsonData["refresh_token"].asString();
        }
        if (jsonData.isMember("expires_in")) {
            expires_in = jsonData["expires_in"].asInt();
        }
    }
    
    return std::make_tuple(access_token, refresh_token, expires_in);
}

std::tuple<std::string, std::string, int> GoogleOAuth::getAccessToken(const std::string& auth_code) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    
    if(curl) {
        std::string postFields = "code=" + auth_code +
                                "&client_id=" + client_id +
                                "&client_secret=" + client_secret +
                                "&redirect_uri=" + redirect_uri +
                                "&grant_type=authorization_code";
                                
        curl_easy_setopt(curl, CURLOPT_URL, "https://oauth2.googleapis.com/token");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        
        curl_easy_cleanup(curl);
    }
    
    return extractTokens(readBuffer);
}

TokenResponse GoogleOAuth::refreshAccessToken() {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    TokenResponse tokenResponse = {"", 0};

    if (curl) {
        std::string postFields = "client_id=" + client_id +
                                "&client_secret=" + client_secret +
                                "&refresh_token=" + refresh_token +
                                "&grant_type=refresh_token";
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://oauth2.googleapis.com/token");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            auto [access_token, _, expires_in] = extractTokens(readBuffer);
            tokenResponse.access_token = access_token;
            tokenResponse.expires_in = expires_in;
            updateExpiryTime(expires_in);
        }

        curl_easy_cleanup(curl);
    }

    return tokenResponse;
}

bool GoogleOAuth::isTokenExpired() const {
    return std::chrono::system_clock::now() >= token_expiry_time;
}

void GoogleOAuth::updateExpiryTime(int expires_in) {
    token_expiry_time = std::chrono::system_clock::now() + 
                        std::chrono::seconds(expires_in - buffer_time);
}