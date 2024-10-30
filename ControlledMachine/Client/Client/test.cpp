#include "GoogleDriveAPI.h"
#include <iostream>
#include <vector>
#include <string>

const std::string client_id_drive = "406151454730-tf8nb9n3aku685cdf9kebmnfm9mdnj0d.apps.googleusercontent.com";
const std::string client_secret_drive = "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";
const std::string redirect_uri_drive = "urn:ietf:wg:oauth:2.0:oob";
const std::string refresh_token_drive = "1//0eRpyvzyjcFc-CgYIARAAGA4SNgF-L9IrnRlL8YMO7nG97jh_paO76fbsgi7LD2tz-r40T8hJipsZQjG6usHtX8eZVs64QQtHVA"; //4/1AVG7fiRaDYVTeSLweVkc9j3hhLiF-BfSQmICL2IFN9UHgjTIRFl6CdNeods    "1//0eIEkjQbra3JLCgYIARAAGA4SNgF-L9Irmy1vV95LbvzisbEF4aQMZYpIPU3H4-_lejLLIG43JVL0AlxE3QA6OLw4j0c_NkVfXA";

int main()
{
    std::vector<std::string> emailList;
    emailList.push_back("ndhung23@clc.fitus.edu.vn");
    GoogleDriveAPI drive(client_id_drive, client_secret_drive, redirect_uri_drive, refresh_token_drive);
    std::string fileLink = drive.uploadFile("D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/testUpload.txt", "testUpload.txt", emailList);
    std::cout << fileLink;
    return 0;
}