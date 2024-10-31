#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <windows.h>

// Make running variable static so it can be accessed by multiple functions
static std::atomic<bool> running{true};

void displayKeyPress(const char* action, int key) {
    std::cout << action << ": " << (char)key 
              << " (ASCII: " << key << ")" << std::endl;
}

void keyboardMonitor() {
    std::cout << "Keyboard monitoring started. Press ESC to exit.\n";
    
    while(running) {
        for(int key = 8; key <= 255; key++) {
            if(GetAsyncKeyState(key) == -32767) {
                displayKeyPress("Key pressed", key);
                
                if(key == VK_ESCAPE) {
                    running = false;
                    break;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// New function to stop the monitoring
void stopMonitoring() {
    running = false;
    std::cout << "Stopping keyboard monitor...\n";
}

// Example of how to use timer to stop monitoring after specific duration
void stopAfterDelay(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    stopMonitoring();
}

int main() {
    std::cout << "Starting keyboard input monitor...\n";
    std::cout << "All keyboard input will be displayed in this window.\n";
    std::cout << "This program runs with user awareness for input testing.\n";
    std::cout << "Program will stop after 10 seconds or press ESC to exit.\n\n";

    // Start monitoring thread
    std::thread monitorThread(keyboardMonitor);
    
    // Create another thread to stop monitoring after 10 seconds
    std::thread timerThread(stopAfterDelay, 10);
    
    // Wait for monitoring thread to finish
    monitorThread.join();
    
    // Wait for timer thread to finish
    timerThread.join();
    
    std::cout << "\nKeyboard monitoring stopped.\n";
    return 0;
}