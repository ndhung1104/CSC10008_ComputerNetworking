// g++ getParameters.cpp jsoncpp.cpp  -o getParameters -I".\lib\curl\include" -L".\lib\curl\lib" -lcurl -lws2_32

#include <iostream>
#include <curl/curl.h>
#include "json/json.h"
#include <fstream>
#include <sstream>

const std::string client_ip = "10.122.1.138";

const std::string client_id_gmail = "406151454730-q8sbba0gq585nojc2al4351s27ksog0g.apps.googleusercontent.com";
const std::string client_secret_gmail = "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";
const std::string redirect_uri_gmail = "urn:ietf:wg:oauth:2.0:oob";
    
const std::string client_id_drive = "406151454730-tf8nb9n3aku685cdf9kebmnfm9mdnj0d.apps.googleusercontent.com";
const std::string client_secret_drive = "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";
const std::string redirect_uri_drive = "urn:ietf:wg:oauth:2.0:oob";

// Helper function to handle HTTP response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to get access token from authorization code
std::tuple<std::string, std::string, int> getTokens(const std::string& auth_code, const std::string& client_id, const std::string& client_secret, const std::string& redirect_uri) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::string postFields = "code=" + auth_code +
                                 "&client_id=" + client_id +
                                 "&client_secret=" + client_secret +
                                 "&redirect_uri=" + redirect_uri +
                                 "&grant_type=authorization_code";
        curl_easy_setopt(curl, CURLOPT_URL, "https://oauth2.googleapis.com/token");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    Json::Value jsonData;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream s(readBuffer);

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
int main() {
    std::string gmail_auth_code, drive_auth_code;

    // URLs for Gmail and Drive authorization
    std::cout << "Visit the following URLs to get the authorization codes:\n";

    std::cout << "\n1. Gmail API:" << std::endl;
    std::cout << "https://accounts.google.com/o/oauth2/auth?client_id=" << client_id_gmail
              << "&redirect_uri=" << redirect_uri_gmail
              << "&scope=https://www.googleapis.com/auth/gmail.modify"
              << "&response_type=code" << std::endl;

    // Input the authorization codes
    std::cout << "\nEnter the Gmail API authorization code: ";
    std::cin >> gmail_auth_code;
    auto [gmail_access_token, gmail_refresh_token, gmail_expires_in] = getTokens(gmail_auth_code, client_id_gmail, client_secret_gmail, redirect_uri_gmail);

    std::cout << "\n2. Google Drive API:" << std::endl;
    std::cout << "https://accounts.google.com/o/oauth2/auth?client_id=" << client_id_drive
              << "&redirect_uri=" << redirect_uri_drive
              << "&scope=https://www.googleapis.com/auth/drive.file"
              << "&response_type=code" << std::endl;

    std::cout << "Enter the Google Drive API authorization code: ";
    std::cin >> drive_auth_code;

    // Get tokens for Gmail API
    

    // Get tokens for Google Drive API
    auto [drive_access_token, drive_refresh_token, drive_expires_in] = getTokens(drive_auth_code, client_id_drive, client_secret_drive, redirect_uri_drive);

    // Output the tokens
    std::ofstream ofs("parameters.txt");

    ofs << client_ip << "\n" << gmail_refresh_token << "\n" << drive_refresh_token;

    ofs.close();

    return 0;
}