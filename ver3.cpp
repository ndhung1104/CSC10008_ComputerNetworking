#include <iostream>
#include <curl/curl.h>
#include "json/json.h"
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <tuple>

std::string client_id = "406151454730-q8sbba0gq585nojc2al4351s27ksog0g.apps.googleusercontent.com";
std::string client_secret = "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";
std::string redirect_uri = "urn:ietf:wg:oauth:2.0:oob"; // Redirect for installed apps

const int emailCheckInterval = 60; // e.g., 60 seconds (you can adjust this)
const int bufferTime = 10; // buffer time to refresh token slightly before it expires


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string decodeBase64(const std::string& encoded_str) {
    // Base64 decoding table
    static const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    int in_len = encoded_str.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    std::vector<unsigned char> char_array_4(4), char_array_3(3);
    std::string decoded_str;

    while (in_len-- && (encoded_str[in_] != '=') && isalnum(encoded_str[in_]) || (encoded_str[in_] == '+') || (encoded_str[in_] == '/')) {
        char_array_4[i++] = encoded_str[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                decoded_str += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) decoded_str += char_array_3[j];
    }

    return decoded_str;
}

std::tuple<std::string, std::string, int> extractTokens(const std::string& response) {
    std::string accessTokenKey = "\"access_token\": \"";
    std::string refreshTokenKey = "\"refresh_token\": \"";
    std::string expiresInKey = "\"expires_in\": ";
    size_t startPos, endPos;
    
    // Extract access token
    startPos = response.find(accessTokenKey);
    std::string accessToken = "";
    if (startPos != std::string::npos) {
        startPos += accessTokenKey.length();
        endPos = response.find("\"", startPos);
        accessToken = response.substr(startPos, endPos - startPos);
    }
    
    // Extract refresh token
    startPos = response.find(refreshTokenKey);
    std::string refreshToken = "";
    if (startPos != std::string::npos) {
        startPos += refreshTokenKey.length();
        endPos = response.find("\"", startPos);
        refreshToken = response.substr(startPos, endPos - startPos);
    }

    // Extract expires_in
    startPos = response.find(expiresInKey);
    int expiresIn = 0;
    if (startPos != std::string::npos) {
        startPos += expiresInKey.length();
        endPos = response.find(",", startPos);
        if (endPos == std::string::npos) {
            endPos = response.find("}", startPos);
        }
        expiresIn = std::stoi(response.substr(startPos, endPos - startPos));
    }
    
    return std::make_tuple(accessToken, refreshToken, expiresIn);
}

std::tuple<std::string, std::string, int> getAccessToken(const std::string& auth_code, const std::string& client_id, const std::string& client_secret, const std::string& redirect_uri) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
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
        
        res = curl_easy_perform(curl);
        
        // Debugging output
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            std::cout << "Response: " << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    
    return extractTokens(readBuffer);  // Parse and return access token, refresh token, and expires_in
}

// Function to get email details (sender, subject, and body) using message ID
void getEmailDetails(const std::string& access_token, const std::string& message_id) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://gmail.googleapis.com/gmail/v1/users/me/messages/" + message_id + "?format=full";
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Parse the JSON response
            Json::CharReaderBuilder builder;
            Json::Value jsonData;
            std::string errs;
            std::istringstream s(readBuffer);
            if (Json::parseFromStream(builder, s, &jsonData, &errs)) {
                // Look for headers: 'From', 'Subject'
                std::string sender, subject, body;

                long long internalDate = jsonData["internalDate"].asString().empty() ? 0 : std::stoll(jsonData["internalDate"].asString());
                // std::time_t timestamp = internalDate / 1000; // Convert milliseconds to seconds


                for (const auto& header : jsonData["payload"]["headers"]) {
                    if (header["name"].asString() == "From") {
                        sender = header["value"].asString();
                    }
                    if (header["name"].asString() == "Subject") {
                        subject = header["value"].asString();
                    }
                }

                // Extract the body data
                const Json::Value& parts = jsonData["payload"]["parts"];
                for (const auto& part : parts) {
                    if (part["mimeType"].asString() == "text/plain") {
                        body = part["body"]["data"].asString();
                        break;
                    }
                }

                // Decode the Base64Url-encoded body content
                // This is a simplified decoder, and it assumes no padding (base64url encoding)
                body = decodeBase64(body);

                // Display the email details
                std::cout << "Sender: " << sender << std::endl;
                std::cout << "Subject: " << subject << std::endl;
                std::cout << "Timestamp: " << internalDate << std::endl;
                std::cout << "Body (truncated): " << body << std::endl;
            }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
}

// Function to retrieve a list of email IDs and call getEmailDetails on each
void getEmailList(const std::string& access_token) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://gmail.googleapis.com/gmail/v1/users/me/messages");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Parse the JSON response to get message IDs
            Json::CharReaderBuilder builder;
            Json::Value jsonData;
            std::string errs;
            std::istringstream s(readBuffer);
            if (Json::parseFromStream(builder, s, &jsonData, &errs)) {
                for (const auto& message : jsonData["messages"]) {
                    std::string message_id = message["id"].asString();
                    std::cout << "\nRetrieving details for Message ID: " << message_id << std::endl;
                    getEmailDetails(access_token, message_id);
                }
            }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
}

std::string refreshAccessToken(const std::string& refresh_token, const std::string& client_id, const std::string& client_secret) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string postFields = "client_id=" + client_id +
                                 "&client_secret=" + client_secret +
                                 "&refresh_token=" + refresh_token +
                                 "&grant_type=refresh_token";
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://oauth2.googleapis.com/token");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return "";
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // Parse the access token from response manually
    std::string tokenKey = "\"access_token\": \"";
    size_t startPos = readBuffer.find(tokenKey);
    if (startPos == std::string::npos) return "";
    
    startPos += tokenKey.length();
    size_t endPos = readBuffer.find("\"", startPos);
    
    return readBuffer.substr(startPos, endPos - startPos);
}

int main() {
    std::string auth_code;
    std::cout << "Visit the following URL to get the authorization code:" << std::endl;
    std::cout << "https://accounts.google.com/o/oauth2/auth?client_id=" << client_id
              << "&redirect_uri=" << redirect_uri
              << "&scope=https://www.googleapis.com/auth/gmail.readonly"
              << "&response_type=code" << std::endl;
    std::cout << "Enter the authorization code: ";
    std::cin >> auth_code;

    // Get initial access and refresh tokens
    auto tokens = getAccessToken(auth_code, client_id, client_secret, redirect_uri);
    std::string access_token = std::get<0>(tokens);
    std::string refresh_token = std::get<1>(tokens);
    int expires_in = std::get<2>(tokens);

    // Check if we successfully obtained an access token
    if (access_token.empty()) {
        std::cerr << "Failed to retrieve access token!" << std::endl;
        return 1;
    }

    // Calculate the initial expiration time
    auto tokenExpiryTime = std::chrono::system_clock::now() + std::chrono::seconds(expires_in - bufferTime);

    // Continuous loop to check for new emails and refresh tokens when necessary
    while (true) {
        // Refresh the token if it has expired
        if (std::chrono::system_clock::now() >= tokenExpiryTime) {
            access_token = refreshAccessToken(refresh_token, client_id, client_secret);
            if (access_token.empty()) {
                std::cerr << "Failed to refresh access token!" << std::endl;
                break;
            }
            std::cout << "Access Token refreshed successfully!" << std::endl;

            // Reset the token expiry time (e.g., assuming new token valid for the same amount of time)
            tokenExpiryTime = std::chrono::system_clock::now() + std::chrono::seconds(expires_in - bufferTime);
        }

        // Check for new emails
        getEmailList(access_token);

        // Sleep for the email check interval before checking again
        std::this_thread::sleep_for(std::chrono::seconds(emailCheckInterval));
    }

    return 0;
}

// int main() {
//     std::string auth_code;
//     std::cout << "Visit the following URL to get the authorization code:" << std::endl;
//     std::cout << "https://accounts.google.com/o/oauth2/auth?client_id=" << client_id
//               << "&redirect_uri=" << redirect_uri
//               << "&scope=https://www.googleapis.com/auth/gmail.readonly"
//               << "&response_type=code" << std::endl;
//     std::cout << "Enter the authorization code: ";
//     std::cin >> auth_code;

//     auto tokens = getAccessToken(auth_code, client_id, client_secret, redirect_uri);
//     std::string access_token = std::get<0>(tokens);
//     std::string refresh_token = std::get<1>(tokens);
//     int expires_in = std::get<2>(tokens);

//     if (!access_token.empty()) {
//         std::cout << "Access Token: " << access_token << std::endl;
//         std::cout << "Refresh Token: " << refresh_token << std::endl;
//         std::cout << "Expires In: " << expires_in << " seconds" << std::endl;
        
//         // Now use access_token to make authorized requests
//         getEmailList(access_token);
//     } else {
//         std::cerr << "Failed to retrieve access token!" << std::endl;
//     }

//     return 0;
// }

