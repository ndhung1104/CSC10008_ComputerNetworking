#include <iostream>
#include <curl/curl.h>
#include "json/json.h"
#include <fstream>
#include <sstream>

const std::string client_id_drive = "406151454730-tf8nb9n3aku685cdf9kebmnfm9mdnj0d.apps.googleusercontent.com";
const std::string client_secret_drive = "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";
const std::string redirect_uri_drive = "urn:ietf:wg:oauth:2.0:oob";
const std::string refresh_token_drive = "1//0eRpyvzyjcFc-CgYIARAAGA4SNgF-L9IrnRlL8YMO7nG97jh_paO76fbsgi7LD2tz-r40T8hJipsZQjG6usHtX8eZVs64QQtHVA"; //4/1AVG7fiRaDYVTeSLweVkc9j3hhLiF-BfSQmICL2IFN9UHgjTIRFl6CdNeods    "1//0eIEkjQbra3JLCgYIARAAGA4SNgF-L9Irmy1vV95LbvzisbEF4aQMZYpIPU3H4-_lejLLIG43JVL0AlxE3QA6OLw4j0c_NkVfXA";

const std::string client_id = "406151454730-q8sbba0gq585nojc2al4351s27ksog0g.apps.googleusercontent.com";
const std::string client_secret = "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";
const std::string redirect_uri = "urn:ietf:wg:oauth:2.0:oob";

// Helper function to handle HTTP response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to get access token from authorization code
std::string getAccessToken(const std::string& auth_code) {
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
        
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    
    Json::Value jsonData;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream s(readBuffer);
    std::cout << readBuffer << std::endl;
    if (Json::parseFromStream(builder, s, &jsonData, &errs)) {
        return jsonData["access_token"].asString();
    }

    return "";
}

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

        Json::Value jsonData;
        Json::CharReaderBuilder builder;
        std::string errs;
        std::istringstream s(readBuffer);
        if (Json::parseFromStream(builder, s, &jsonData, &errs)) {
            std::cout << "User's email: " << jsonData["emailAddress"].asString() << std::endl;
        }
    }
}

// int main() {
//     std::string auth_code;
//     std::cout << "Visit the following URL to get authorization code:" << std::endl;
//     std::cout << "https://accounts.google.com/o/oauth2/auth?client_id=" << client_id
//               << "&redirect_uri=" << redirect_uri
//               << "&scope=https://www.googleapis.com/auth/gmail.modify"  //drive.file
//               << "&response_type=code" << std::endl;
//     std::cout << "Enter the authorization code: ";
//     std::cin >> auth_code;

//     std::string access_token = getAccessToken(auth_code);
//     // if (!access_token.empty()) {
//     //     getUserEmail(access_token);
//     // } else {
//     //     std::cerr << "Failed to retrieve access token!" << std::endl;
//     // }

//     return 0;
// }
