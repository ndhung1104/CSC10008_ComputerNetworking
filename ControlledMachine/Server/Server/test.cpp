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

    std::wstring sanitizeString(const std::wstring& str) {
        std::wstring sanitized;
        for (const wchar_t& ch : str) {
            if (iswprint(ch)) { // Check if the character is printable
                sanitized += ch;
            }
        }
        return sanitized;
    }

    std::vector<ServiceInfo> listServices() {
        std::vector<ServiceInfo> services;

        SC_HANDLE scmHandle = OpenSCManager(nullptr, nullptr, SC_MANAGER_ENUMERATE_SERVICE);
        if (!scmHandle) {
            std::wcerr << L"Failed to open service control manager: " << GetLastError() << std::endl;
            return services;
        }

        DWORD bytesNeeded = 0, serviceCount = 0;
        EnumServicesStatusEx(
            scmHandle, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL, nullptr, 0, 
            &bytesNeeded, &serviceCount, nullptr, nullptr
        );

        std::vector<BYTE> buffer(bytesNeeded);
        LPENUM_SERVICE_STATUS_PROCESS servicesArray = 
            reinterpret_cast<LPENUM_SERVICE_STATUS_PROCESS>(buffer.data());

        if (EnumServicesStatusEx(
                scmHandle, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
                reinterpret_cast<LPBYTE>(servicesArray), bytesNeeded, &bytesNeeded, 
                &serviceCount, nullptr, nullptr)) {
            
            for (DWORD i = 0; i < serviceCount; i++) {
                ServiceInfo service;
                service.name = sanitizeString(servicesArray[i].lpServiceName);
                service.displayName = sanitizeString(servicesArray[i].lpDisplayName);
                services.push_back(service);
                std::wcout << L"Service Name: " << servicesArray[i].lpServiceName << std::endl;

                // Print the length of the display name for further analysis
                // std::wstring displayName(servicesArray[i].lpDisplayName);
                // std::wcerr << L"Display Name Length: " << displayName.length() << std::endl;
                std::wcout << L"Display Name: " << servicesArray[i].lpDisplayName << std::endl;
                // printHex(service.name);
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
        SC_HANDLE scmHandle = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
        if (!scmHandle) {
            std::wcerr << L"Failed to open service control manager: " << GetLastError() << std::endl;
            return false;
        }

        SC_HANDLE serviceHandle = OpenService(scmHandle, serviceName.c_str(), SERVICE_START);
        if (!serviceHandle) {
            std::wcerr << L"Failed to open service: " << GetLastError() << std::endl;
            CloseServiceHandle(scmHandle);
            return false;
        }

        bool result = StartService(serviceHandle, 0, nullptr);
        if (!result) {
            std::wcerr << L"Failed to start service: " << GetLastError() << std::endl;
        } else {
            std::wcout << L"Service started successfully.\n";
        }

        CloseServiceHandle(serviceHandle);
        CloseServiceHandle(scmHandle);
        return result;
    }

    // bool saveServicesToFile(const std::vector<ServiceInfo>& services, const std::wstring& filePath) {
    //     std::wofstream outputFile(filePath.c_str());
    //     if (!outputFile) {
    //         std::wcerr << L"Error opening file for writing." << std::endl;
    //         return false;
    //     }

    //     for (size_t i = 0; i < services.size(); ++i) {
    //         outputFile << i + 1 << L". " << services[i].name 
    //                    << L" (" << services[i].displayName << L")" << std::endl;
    //     }
    //     outputFile.close();

    //     return true;
    // }

    void saveServicesToFile(const std::vector<ServiceInfo>& services, const std::wstring& filePath) {
        std::wofstream outputFile(filePath.c_str());
        if (!outputFile) {
            std::wcerr << L"Error opening file for writing." << std::endl;
            return;
        }

        for (size_t i = 0; i < services.size(); ++i) {
            const auto& service = services[i];

            // Check if the service name and display name are valid
            if (service.name.empty() || service.displayName.empty()) {
                std::wcerr << L"Invalid service data at index " << i << L": "
                            << L"Name: " << service.name << L", DisplayName: " << service.displayName << std::endl;
                continue; // Skip this service
            }

            

            // Output to console for debugging
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
        SC_HANDLE scmHandle = OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);
        if (!scmHandle) {
            std::wcerr << L"Failed to open service control manager: " << GetLastError() << std::endl;
            return false;
        }

        SC_HANDLE serviceHandle = OpenService(scmHandle, serviceName.c_str(), SERVICE_STOP);
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

int main() {
    ServiceManager serviceManager;
    std::vector<ServiceManager::ServiceInfo> services = serviceManager.listServices();
    std::cout << services.size() << "\n";
    if (services.empty()) {
        std::wcout << L"No services found.\n";
        return 0;
    }
    serviceManager.saveServicesToFile(services, L"listservices.txt");

    std::wcout << L"Available Services:\n";
    for (size_t i = 0; i < services.size(); i++) {
        std::wcout << i + 1 << L". " << services[i].displayName << L" (" << services[i].name << L")\n";
        if (std::wcout.fail())
                std::wcout.clear();
    }

    size_t choice;
    std::wcout << L"\nEnter the number of the service to manage: ";
    std::wcin >> choice;

    if (choice < 1 || choice > services.size()) {
        std::wcerr << L"Invalid selection.\n";
        return 1;
    }

    std::wstring selectedService = services[choice - 1].name;

    std::wcout << L"Do you want to (1) Start or (2) Stop the service? ";
    int action;
    std::wcin >> action;

    if (action == 1) {
        serviceManager.startService(selectedService);
    } else if (action == 2) {
        serviceManager.stopService(selectedService);
    } else {
        std::wcerr << L"Invalid action.\n";
    }

    return 0;
}
