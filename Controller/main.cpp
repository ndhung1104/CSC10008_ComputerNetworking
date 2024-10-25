#include "EmailMonitor.h"
#include <iostream>

int main() {
    const std::string client_id = "406151454730-q8sbba0gq585nojc2al4351s27ksog0g.apps.googleusercontent.com";
    const std::string client_secret = "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";
    const std::string redirect_uri = "urn:ietf:wg:oauth:2.0:oob";
    const std::string refresh_token = "1//0eaewHpRVZdWcCgYIARAAGA4SNgF-L9IrFKbFWQHsu52H5UWxLtNDh9VRCsgns-WHr4ageQD4-kPO7Unp7EXyopno-iP1RLweNg"; //"1//0eIEkjQbra3JLCgYIARAAGA4SNgF-L9Irmy1vV95LbvzisbEF4aQMZYpIPU3H4-_lejLLIG43JVL0AlxE3QA6OLw4j0c_NkVfXA";
    
    EmailMonitor monitor(client_id, client_secret, redirect_uri, refresh_token);
    // std::string auth_code;
    // std::cout << "Visit the following URL to get the authorization code:" << std::endl;
    // std::cout << "https://accounts.google.com/o/oauth2/auth?client_id=" << client_id
    //           << "&redirect_uri=" << redirect_uri
    //           << "&scope=https://www.googleapis.com/auth/gmail.modify"
    //           << "&response_type=code" << std::endl;
    // std::cout << "Enter the authorization code: ";
    // std::cin >> auth_code;
    // auto [access_token1, refresh_token1, expires_in1] = monitor.oauth.getAccessToken(auth_code);
    // std::cout << access_token1 << "\n" << refresh_token1 << "\n" << expires_in1 << "\n";
    monitor.start();
    
    return 0;
}