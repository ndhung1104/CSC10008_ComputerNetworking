#include "GmailAPI.h"
#include <curl/curl.h>
#include "json/json.h"
#include <iostream>
#include <sstream>
#include <regex>

GmailAPI::GmailAPI(GoogleOAuth& oauth) : oauth(oauth) {}

size_t GmailAPI::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string GmailAPI::extractEmail(const std::string& fullSender) {
    std::regex emailRegex("<(.+?)>");
    std::smatch match;
    
    if (std::regex_search(fullSender, match, emailRegex)) {
        return match[1];  // Extracted email address
    }
    return fullSender;  // Return original if no match is found
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

std::string GmailAPI::base64Encode(const std::string& input) {
    static const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::string encoded;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    size_t in_len = input.length();
    const unsigned char* bytes_to_encode = reinterpret_cast<const unsigned char*>(input.c_str());

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                encoded += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; j < i + 1; j++)
            encoded += base64_chars[char_array_4[j]];

        while (i++ < 3)
            encoded += '=';
    }

    return encoded;
}

bool GmailAPI::sendEmail(const std::string& access_token,
                        const std::string& to,
                        const std::string& subject,
                        const std::string& body) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    bool success = false;

    if (curl) {
        std::string url = "https://gmail.googleapis.com/gmail/v1/users/me/messages/send";
        
        // Create email message in RFC 2822 format
        std::string email_content = "To: " + to + "\r\n";
        email_content += "Subject: " + subject + "\r\n";
        email_content += "Content-Type: text/plain; charset=utf-8\r\n\r\n";
        email_content += body;

        // Create JSON payload with base64 encoded email
        std::string encoded_email = base64Encode(email_content);
        std::string postData = "{\"raw\":\"" + encoded_email + "\"}";
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            Json::CharReaderBuilder builder;
            Json::Value root;
            std::string errors;
            std::istringstream responseStream(readBuffer);
            
            if (Json::parseFromStream(builder, responseStream, &root, &errors)) {
                // Check if the send was successful
                success = !root["id"].empty();
                if (success) {
                    std::cout << "Email sent successfully. Message ID: " << root["id"].asString() << std::endl;
                } else {
                    std::cout << "Failed to send email. Response: " << readBuffer << std::endl;
                }
            }
        } else {
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return success;
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
                        std::string fullSender = header["value"].asString();
                        sender = extractEmail(fullSender);  // Extracted email address only
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
                email newMail;
                newMail.sender = sender;
                newMail.internalDate = internalDate;
                newMail.subject = subject;
                newMail.body = body;
                receivedEmail.push_back(newMail);
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

