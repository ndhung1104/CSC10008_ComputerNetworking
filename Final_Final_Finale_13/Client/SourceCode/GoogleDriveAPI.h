#pragma once
#include <string>
#include "GoogleOAuth.h"
#include <vector>

class GoogleDriveAPI {
public:
    GoogleDriveAPI(const std::string& client_id,
                         const std::string& client_secret,
                         const std::string& redirect_uri,
                         const std::string& refresh_token);
    std::string uploadFile(const std::string& filePath, const std::string& fileName, const std::vector<std::string>& emailAddresses);

private:
    GoogleOAuth oauth;
    std::string getFileLink(const std::string& fileId);
    std::string getMimeType(const std::string& filename);
    bool shareFile(const std::string& fileId, const std::vector<std::string>& emailAddresses);
};

