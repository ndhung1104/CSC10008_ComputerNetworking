#include "GmailAPI.h"
#include <curl/curl.h>
#include "json/json.h"
#include <iostream>
#include <sstream>
#include <vector>

GmailAPI::GmailAPI(GoogleOAuth& oauth) : oauth(oauth) {}

size_t GmailAPI::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string GmailAPI::decodeBase64(const std::string& encoded_str) {
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

void GmailAPI::getEmailDetails(const std::string& access_token, const std::string& message_id) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if (curl) {
        std::string url = "https://gmail.googleapis.com/gmail/v1/users/me/messages/" + 
                         message_id + "?format=full";
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
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

void GmailAPI::getEmailList(const std::string& access_token, const std::string& query) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if (curl) {
        char* encoded_query = curl_easy_escape(curl, query.c_str(), query.length());
        std::string url = "https://gmail.googleapis.com/gmail/v1/users/me/messages?q=" + 
                         std::string(encoded_query);
        curl_free(encoded_query);
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            Json::CharReaderBuilder builder;
            Json::Value jsonData;
            std::string errs;
            std::istringstream s(readBuffer);
            if (Json::parseFromStream(builder, s, &jsonData, &errs)) {
                for (const auto& message : jsonData["messages"]) {
                    std::string message_id = message["id"].asString();
                    std::cout << "\nRetrieving details for Message ID: " << message_id << std::endl;
                    getEmailDetails(access_token, message_id);
                    
                    if (markAsRead(access_token, message_id))
                        std::cout << "\nMarking it as read: " << message_id << std::endl;
                    else
                        std::cout << "\nFailed to mark it as read: " << message_id << std::endl;
                }
            }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
}

bool GmailAPI::markAsRead(const std::string& access_token, const std::string& message_id) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    bool success = false;

    if (curl) {
        std::string url = "https://gmail.googleapis.com/gmail/v1/users/me/messages/" + 
                         message_id + "/modify";
        
        // Create the JSON payload
        std::string postData = R"({"removeLabelIds": ["UNREAD"]})";
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");  // Using POST for modify
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        // std::cout << "Response from Gmail API: " << readBuffer << std::endl;
        if (res == CURLE_OK) {
            Json::CharReaderBuilder builder;
            Json::Value root;
            std::string errors;
            std::istringstream responseStream(readBuffer);
            
            if (Json::parseFromStream(builder, responseStream, &root, &errors)) {
                // Check if the modification was successful
                success = !root["id"].empty();
            }
        }
        else {
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return success;
}