#include "GoogleDriveAPI.h"
#include <curl/curl.h>
#include "json/json.h"
#include <fstream>
#include <sstream>
#include <iostream>

GoogleDriveAPI::GoogleDriveAPI(const std::string& client_id,
                         const std::string& client_secret,
                         const std::string& redirect_uri,
                         const std::string& refresh_token) : oauth(client_id, client_secret, redirect_uri, refresh_token) {};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string GoogleDriveAPI::getMimeType(const std::string& filename) {
    // This is a simple implementation; adjust as needed for other MIME types
    size_t extPos = filename.find_last_of(".");
    std::string ext = filename.substr(extPos + 1);
    if (ext == "txt") return "text/plain";
    if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
    if (ext == "png") return "image/png";
    return "application/octet-stream"; // default for binary files
}

std::string GoogleDriveAPI::uploadFile(const std::string& filePath, const std::string& fileName, const std::vector<std::string>& emailAddresses) {
    std::string mimeType = getMimeType(fileName);
    std::string accessToken = oauth.refreshAccessToken().access_token;

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return "";
    }

    // Read file content
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return "";
    }
    std::ostringstream fileContentStream;
    fileContentStream << file.rdbuf();
    std::string fileContent = fileContentStream.str();

    // Set up boundary and request body
    std::string boundary = "boundary_string";
    std::ostringstream requestBody;
    requestBody << "--" << boundary << "\r\n"
                << "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                << "{\"name\": \"" << fileName << "\"}\r\n"
                << "--" << boundary << "\r\n"
                << "Content-Type: " << mimeType << "\r\n\r\n"
                << fileContent << "\r\n"
                << "--" << boundary << "--\r\n";

    std::string requestBodyStr = requestBody.str();

    // Configure CURL
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + accessToken).c_str());
    headers = curl_slist_append(headers, ("Content-Type: multipart/related; boundary=" + boundary).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, "https://www.googleapis.com/upload/drive/v3/files?uploadType=multipart");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBodyStr.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestBodyStr.size());

    // Capture response
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return "";
    } else {
        std::cout << "File uploaded successfully." << std::endl;
    }

    // Parse the response to get the file ID
    Json::Value jsonResponse;
    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    std::istringstream responseStream(response);
    
    if (!Json::parseFromStream(readerBuilder, responseStream, &jsonResponse, &errors)) {
        std::cerr << "Failed to parse response: " << errors << std::endl;
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return "";
    }

    std::string fileId = jsonResponse["id"].asString(); // Extract the file ID
    std::string fileLink = getFileLink(fileId); // Construct the file link

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    
    if (shareFile(fileId, emailAddresses))
    {
        std::cout << "\nFile sharing successfully!\n";
    }
    
    return fileLink; // Return the link to the uploaded file
}

bool GoogleDriveAPI::shareFile(const std::string& fileId, const std::vector<std::string>& emailAddresses) {
    std::string accessToken = oauth.refreshAccessToken().access_token;

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return false;
    }

    // Configure CURL headers
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + accessToken).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    for (const auto& email : emailAddresses) {
        // Create the permission JSON for each email address
        Json::Value permissionJson;
        permissionJson["role"] = "reader"; // or "writer", depending on your requirement
        permissionJson["type"] = "user"; // Share with a user
        permissionJson["emailAddress"] = email; // Correctly set the email address directly

        // Convert JSON to string
        Json::StreamWriterBuilder writer;
        std::string permissionBody = Json::writeString(writer, permissionJson);

        // Configure CURL
        curl_easy_setopt(curl, CURLOPT_URL, ("https://www.googleapis.com/drive/v3/files/" + fileId + "/permissions").c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, permissionBody.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, permissionBody.size());

        // Perform the CURL request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            return false;
        } else {
            std::cout << "File shared successfully with " << email << "." << std::endl;
        }
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return true;
}
//     std::string response;
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, void* userp) {
//         ((std::string*)userp)->append((char*)contents, size * nmemb);
//         return size * nmemb;
//     });
//     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

//     CURLcode res = curl_easy_perform(curl);
//     if (res != CURLE_OK) {
//         std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
//     } else {
//         std::cout << "File uploaded successfully." << std::endl;
//     }

//     curl_slist_free_all(headers);
//     curl_easy_cleanup(curl);

//     return response;
// }

std::string GoogleDriveAPI::getFileLink(const std::string& fileId) {
    return "https://drive.google.com/file/d/" + fileId + "/view?usp=sharing";
}
