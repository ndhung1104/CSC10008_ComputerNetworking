#define UNICODE
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class ServiceManager {
public:
    struct ServiceInfo {
        std::wstring name;
        std::wstring displayName;
    };

    std::wstring sanitizeString(LPCWSTR str) {
        if (!str) return L"";
        std::wstring sanitized;
        while (*str) {
            if (iswprint(*str)) {
                sanitized += *str;
            }
            str++;
        }
        return sanitized;
    }

    std::vector<ServiceInfo> listServices() {
        std::vector<ServiceInfo> services;

        SC_HANDLE scmHandle = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ENUMERATE_SERVICE);
        if (!scmHandle) {
            std::wcerr << L"Failed to open service control manager: " << GetLastError() << std::endl;
            return services;
        }

        DWORD bytesNeeded = 0, serviceCount = 0;
        EnumServicesStatusExW(
            scmHandle, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL, nullptr, 0, 
            &bytesNeeded, &serviceCount, nullptr, nullptr
        );

        std::vector<BYTE> buffer(bytesNeeded);
        LPENUM_SERVICE_STATUS_PROCESSW servicesArray = 
            reinterpret_cast<LPENUM_SERVICE_STATUS_PROCESSW>(buffer.data());

        if (EnumServicesStatusExW(
                scmHandle, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
                buffer.data(), bytesNeeded, &bytesNeeded, 
                &serviceCount, nullptr, nullptr)) {
            
            for (DWORD i = 0; i < serviceCount; i++) {
                ServiceInfo service;
                service.name = sanitizeString(servicesArray[i].lpServiceName);
                service.displayName = sanitizeString(servicesArray[i].lpDisplayName);
                services.push_back(service);
                
                std::wcout << L"Service Name: " << servicesArray[i].lpServiceName << std::endl;
                std::wcout << L"Display Name: " << servicesArray[i].lpDisplayName << std::endl;
                std::wcout << L"Status: ";
                
                if (std::wcout.fail())
                    std::wcout.clear();
                    
                switch (servicesArray[i].ServiceStatusProcess.dwCurrentState) {
                    case SERVICE_STOPPED: std::wcout << L"Stopped"; break;
                    case SERVICE_START_PENDING: std::wcout << L"Start Pending"; break;
                    case SERVICE_STOP_PENDING: std::wcout << L"Stop Pending"; break;
                    case SERVICE_RUNNING: std::wcout << L"Running"; break;
                    case SERVICE_CONTINUE_PENDING: std::wcout << L"Continue Pending"; break;
                    case SERVICE_PAUSE_PENDING: std::wcout << L"Pause Pending"; break;
                    case SERVICE_PAUSED: std::wcout << L"Paused"; break;
                    default: std::wcout << L"Unknown"; break;
                }
                std::wcout << std::endl << std::endl;
            }
        } else {
            std::wcerr << L"Failed to enumerate services: " << GetLastError() << std::endl;
        }

        CloseServiceHandle(scmHandle);
        return services;
    }

    bool startService(const std::wstring& serviceName) {
        SC_HANDLE scmHandle = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CONNECT);
        if (!scmHandle) {
            std::wcerr << L"Failed to open service control manager: " << GetLastError() << std::endl;
            return false;
        }

        SC_HANDLE serviceHandle = OpenServiceW(scmHandle, serviceName.c_str(), SERVICE_START);
        if (!serviceHandle) {
            std::wcerr << L"Failed to open service: " << GetLastError() << std::endl;
            CloseServiceHandle(scmHandle);
            return false;
        }

        bool result = StartServiceW(serviceHandle, 0, nullptr);
        if (!result) {
            std::wcerr << L"Failed to start service: " << GetLastError() << std::endl;
        } else {
            std::wcout << L"Service started successfully.\n";
        }

        CloseServiceHandle(serviceHandle);
        CloseServiceHandle(scmHandle);
        return result;
    }

    void saveServicesToFile(const std::vector<ServiceInfo>& services, const std::wstring& filePath) {
        std::wofstream outputFile(filePath.c_str());
        if (!outputFile) {
            std::wcerr << L"Error opening file for writing." << std::endl;
            return;
        }

        for (size_t i = 0; i < services.size(); ++i) {
            const auto& service = services[i];

            if (service.name.empty() || service.displayName.empty()) {
                std::wcerr << L"Invalid service data at index " << i << L": "
                          << L"Name: " << service.name << L", DisplayName: " << service.displayName << std::endl;
                continue;
            }

            std::wcout << i + 1 << L". " << service.name 
                      << L" (" << service.displayName << L")" << std::endl;
            if (std::wcout.fail())
                std::wcout.clear();
            else
                outputFile << i + 1 << L". " << service.name 
                          << L" (" << service.displayName << L")" << std::endl;
        }

        outputFile.close();
    }

    bool stopService(const std::wstring& serviceName) {
        SC_HANDLE scmHandle = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CONNECT);
        if (!scmHandle) {
            std::wcerr << L"Failed to open service control manager: " << GetLastError() << std::endl;
            return false;
        }

        SC_HANDLE serviceHandle = OpenServiceW(scmHandle, serviceName.c_str(), SERVICE_STOP);
        if (!serviceHandle) {
            std::wcerr << L"Failed to open service: " << GetLastError() << std::endl;
            CloseServiceHandle(scmHandle);
            return false;
        }

        SERVICE_STATUS serviceStatus;
        bool result = ControlService(serviceHandle, SERVICE_CONTROL_STOP, &serviceStatus);
        if (!result) {
            std::wcerr << L"Failed to stop service: " << GetLastError() << std::endl;
        } else {
            std::wcout << L"Service stopped successfully.\n";
        }

        CloseServiceHandle(serviceHandle);
        CloseServiceHandle(scmHandle);
        return result;
    }
};
