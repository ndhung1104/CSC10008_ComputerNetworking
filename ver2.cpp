#include <iostream>
#include <curl/curl.h>
#include "json/json.h"
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <vector>

std::string client_id = "406151454730-q8sbba0gq585nojc2al4351s27ksog0g.apps.googleusercontent.com";
std::string client_secret = "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";
std::string redirect_uri = "urn:ietf:wg:oauth:2.0:oob"; // Redirect for installed apps

// Helper function to handle HTTP response
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

// Base64Url decoder
std::string decodeBase64Url(const std::string& input) {
    std::string base64 = input;
    std::replace(base64.begin(), base64.end(), '-', '+');
    std::replace(base64.begin(), base64.end(), '_', '/');
    while (base64.size() % 4) {
        base64 += '=';
    }
    
    // Your base64 decoding function here
    // For simplicity, we return base64 here, but you need to decode it in practice
    return base64;
}

std::string extractAccessToken(const std::string& response) {
    std::string tokenKey = "\"access_token\": \"";
    size_t startPos = response.find(tokenKey);
    if (startPos == std::string::npos) return "";
    
    startPos += tokenKey.length();
    size_t endPos = response.find("\"", startPos);
    
    return response.substr(startPos, endPos - startPos);
}

std::string getAccessToken(const std::string& auth_code, const std::string& client_id, const std::string& client_secret, const std::string& redirect_uri) {
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
        
        // if(res != CURLE_OK) {
        //     fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        // } else {
        //     std::cout << "Response: " << readBuffer << std::endl; // Debugging: print the response
        // }

        curl_easy_cleanup(curl);
    }
    
    return extractAccessToken(readBuffer);  // Parse and return the access token
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

    std::string access_token = getAccessToken(auth_code, client_id, client_secret, redirect_uri);
    if (!access_token.empty()) {
        std::cout << "Access Token: " << access_token << std::endl;
        // Now use access_token to make authorized requests
        // getUserEmail(access_token);
        getEmailList(access_token);
    } else {
        std::cerr << "Failed to retrieve access token!" << std::endl;
    }

    return 0;
}
