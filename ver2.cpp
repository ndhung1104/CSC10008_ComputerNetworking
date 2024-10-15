#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <fstream>
#include <sstream>

std::string client_id = "406151454730-q8sbba0gq585nojc2al4351s27ksog0g.apps.googleusercontent.com";
std::string client_secret = "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";
std::string redirect_uri = "urn:ietf:wg:oauth:2.0:oob"; // Redirect for installed apps

// Helper function to handle HTTP response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
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

void getEmailDetails(const std::string& access_token, const std::string& message_id) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://gmail.googleapis.com/gmail/v1/users/me/messages/" + message_id;
        
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
            // Output the response to show email content (subject, etc.)
            std::cout << "Email Details Response: " << readBuffer << std::endl;

            // Look for the "subject" and "body" fields within the response (simplified parsing)
            size_t subjectPos = readBuffer.find("\"name\": \"Subject\"");
            if (subjectPos != std::string::npos) {
                size_t start = readBuffer.find("\"value\": \"", subjectPos) + 10;
                size_t end = readBuffer.find("\"", start);
                std::string subject = readBuffer.substr(start, end - start);
                std::cout << "Subject: " << subject << std::endl;
            }
            
            size_t bodyPos = readBuffer.find("\"data\": \"");
            if (bodyPos != std::string::npos) {
                size_t start = bodyPos + 9;
                size_t end = readBuffer.find("\"", start);
                std::string body = readBuffer.substr(start, end - start);
                std::cout << "Body (truncated): " << body.substr(0, 100) << "..." << std::endl;  // Show a preview
            }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
}

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
            std::cout << "Email List Response: " << readBuffer << std::endl;

            // Example of extracting message IDs (basic parsing)
            size_t pos = 0;
            std::string idToken = "\"id\": \"";
            while ((pos = readBuffer.find(idToken, pos)) != std::string::npos) {
                pos += idToken.length();
                size_t endPos = readBuffer.find("\"", pos);
                std::string message_id = readBuffer.substr(pos, endPos - pos);
                std::cout << "\nRetrieving details for Message ID: " << message_id << std::endl;
                getEmailDetails(access_token, message_id);
            }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
}

// void getEmailList(const std::string& access_token) {
//     CURL* curl;
//     CURLcode res;
//     std::string readBuffer;

//     curl = curl_easy_init();
//     if (curl) {
//         struct curl_slist* headers = NULL;
//         headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());

//         curl_easy_setopt(curl, CURLOPT_URL, "https://gmail.googleapis.com/gmail/v1/users/me/messages");
//         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

//         res = curl_easy_perform(curl);
//         if (res != CURLE_OK) {
//             fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//         } else {
//             // Output the response (which contains the list of message IDs)
//             std::cout << "Email List Response: " << readBuffer << std::endl;
//         }

//         curl_easy_cleanup(curl);
//         curl_slist_free_all(headers);
//     }
// }

// // Function to get access token from authorization code
// std::string getAccessToken(const std::string& auth_code) {
//     CURL* curl;
//     CURLcode res;
//     std::string readBuffer;
//     curl_global_init(CURL_GLOBAL_DEFAULT);
//     curl = curl_easy_init();
    
//     if(curl) {
//         std::string postFields = "code=" + auth_code +
//                                  "&client_id=" + client_id +
//                                  "&client_secret=" + client_secret +
//                                  "&redirect_uri=" + redirect_uri +
//                                  "&grant_type=authorization_code";
//         curl_easy_setopt(curl, CURLOPT_URL, "https://oauth2.googleapis.com/token");
//         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//         res = curl_easy_perform(curl);
//         std::cout << "Response: " << readBuffer << std::endl;
        
//         if(res != CURLE_OK)
//             fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

//         curl_easy_cleanup(curl);
//     }

//     // Manual parsing of the access token from the response
//     size_t pos = readBuffer.find("access_token\":\"");
//     if (pos != std::string::npos) {
//         pos += 15; // Move past "access_token":""
//         size_t endPos = readBuffer.find("\"", pos);
//         return readBuffer.substr(pos, endPos - pos);
//     }

//     return "";
// }

// Function to get user's email
void getUserEmail(const std::string& access_token) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + access_token).c_str());
        curl_easy_setopt(curl, CURLOPT_URL, "https://gmail.googleapis.com/gmail/v1/users/me/profile");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        // Manual parsing of the email address from the response
        size_t pos = readBuffer.find("emailAddress\":\"");
        if (pos != std::string::npos) {
            pos += 16; // Move past "emailAddress":""
            size_t endPos = readBuffer.find("\"", pos);
            std::cout << "User's email: " << readBuffer.substr(pos, endPos - pos) << std::endl;
        }
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
        getUserEmail(access_token);
        getEmailList(access_token);
    } else {
        std::cerr << "Failed to retrieve access token!" << std::endl;
    }

    return 0;
}

// int main() {
//     std::string auth_code;
//     std::cout << "Visit the following URL to get authorization code:" << std::endl;
//     std::cout << "https://accounts.google.com/o/oauth2/auth?client_id=" << client_id
//               << "&redirect_uri=" << redirect_uri
//               << "&scope=https://www.googleapis.com/auth/gmail.readonly"
//               << "&response_type=code" << std::endl;
//     std::cout << "Enter the authorization code: ";
//     std::cin >> auth_code;

//     std::string access_token = getAccessToken(auth_code);
//     if (!access_token.empty()) {
//         getUserEmail(access_token);
//     } else {
//         std::cerr << "Failed to retrieve access token!" << std::endl;
//     }

//     return 0;
// }
