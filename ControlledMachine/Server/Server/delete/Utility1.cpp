#include "Utility.h"

void shutdown() {
    // Adjust privileges to allow shutdown command
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    // Open a handle to the process access token
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        // Retrieve the shutdown privilege
        LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
        tkp.PrivilegeCount = 1;  // One privilege to adjust
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        // Adjust the process token to allow shutdown
        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);

        // Issue the shutdown command
        if (ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) {
            std::cout << "Shutdown command issued successfully." << std::endl;
        }
        else {
            std::cerr << "Failed to issue shutdown command." << std::endl;
        }
    }
    else {
        std::cerr << "Failed to open process token." << std::endl;
    }

    // Close the handle
    CloseHandle(hToken);
}
void reset() {
    // Adjust privileges to allow reboot command
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    // Open a handle to the process access token
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        // Retrieve the reboot privilege
        LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
        tkp.PrivilegeCount = 1;  // One privilege to adjust
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        // Adjust the process token to allow reboot
        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);

        // Issue the reboot command
        if (ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) {
            std::cout << "Reboot command issued successfully." << std::endl;
        }
        else {
            std::cerr << "Failed to issue reboot command." << std::endl;
        }
    }
    else {
        std::cerr << "Failed to open process token." << std::endl;
    }

    // Close the handle
    CloseHandle(hToken);
}
void keyLogger();
void listApp() {
    std::vector<std::wstring> applications;
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD index = 0;
        wchar_t subKeyName[256];
        DWORD subKeyNameSize = 256;

        // Enumerate subkeys to find each application
        while (RegEnumKeyEx(hKey, index, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
            HKEY hSubKey;
            if (RegOpenKeyEx(hKey, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
                wchar_t appName[256];
                DWORD appNameSize = sizeof(appName);
                DWORD type;

                // Query the display name of the application
                if (RegQueryValueEx(hSubKey, L"DisplayName", NULL, &type, reinterpret_cast<LPBYTE>(appName), &appNameSize) == ERROR_SUCCESS && type == REG_SZ) {
                    applications.push_back(appName);
                }
                RegCloseKey(hSubKey);
            }
            index++;
            subKeyNameSize = 256;
        }
        RegCloseKey(hKey);
    }
    std::wofstream outFile("listApp.txt");

    if (!outFile) {
        std::wcerr << L"Failed to open file for writing: " << fileName << std::endl;
        return;
    }

    for (const auto& app : applications) {
        outFile << app << std::endl;
    }

    outFile.close();
}
void startApp(std::string name);
void stopApp(std::string name);
void listService();
void startService(std::string name);
void stopService(std::string name);
void screenShot();
void copyFile(std::string name);
void startWebcam();
void stopWebcam();