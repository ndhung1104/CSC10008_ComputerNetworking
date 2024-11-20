#include "Utility.h"

void shutdown();
void reset();
void keyLogger();
void listApp();
void startApp(std::string name);
void stopApp(std::string name);
void listService();
void startService(std::string name);
void stopService(std::string name);
// bool Computer::screenShot(const std::string& filename) {
//     // Get the device context of the screen
//     HDC hScreenDC = GetDC(NULL);
//     if (!hScreenDC) {
//         std::cerr << "Failed to get screen DC" << std::endl;
//         return false;
//     }

//     HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
//     if (!hMemoryDC) {
//         ReleaseDC(NULL, hScreenDC);
//         std::cerr << "Failed to create compatible DC" << std::endl;
//         return false;
//     }

//     // Get the dimensions of the screen
//     int width = GetSystemMetrics(SM_CXSCREEN);
//     int height = GetSystemMetrics(SM_CYSCREEN);

//     // Create a bitmap to hold the screenshot
//     HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
//     if (!hBitmap) {
//         DeleteDC(hMemoryDC);
//         ReleaseDC(NULL, hScreenDC);
//         std::cerr << "Failed to create bitmap" << std::endl;
//         return false;
//     }

//     // Select the bitmap into the memory device context
//     HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

//     // Print dimensions for debugging
//     std::cout << "Screen dimensions: " << width << "x" << height << std::endl;

//     // Bit block transfer into the memory device context
//     if (!BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY)) {
//         std::cerr << "BitBlt failed" << std::endl;
//         SelectObject(hMemoryDC, hOldBitmap);
//         DeleteObject(hBitmap);
//         DeleteDC(hMemoryDC);
//         ReleaseDC(NULL, hScreenDC);
//         return false;
//     }

//     // Create bitmap info structure
//     BITMAPINFOHEADER bi;
//     bi.biSize = sizeof(BITMAPINFOHEADER);
//     bi.biWidth = width;
//     bi.biHeight = -height;  // Negative height to ensure correct orientation
//     bi.biPlanes = 1;
//     bi.biBitCount = 32;
//     bi.biCompression = BI_RGB;
//     bi.biSizeImage = 0;
//     bi.biXPelsPerMeter = 0;
//     bi.biYPelsPerMeter = 0;
//     bi.biClrUsed = 0;
//     bi.biClrImportant = 0;

//     // Create OpenCV Mat
//     cv::Mat mat(height, width, CV_8UC4);

//     // Get the bitmap bits
//     if (!GetDIBits(hMemoryDC, hBitmap, 0, height, mat.data,
//                    (BITMAPINFO*)&bi, DIB_RGB_COLORS)) {
//         std::cerr << "GetDIBits failed" << std::endl;
//         SelectObject(hMemoryDC, hOldBitmap);
//         DeleteObject(hBitmap);
//         DeleteDC(hMemoryDC);
//         ReleaseDC(NULL, hScreenDC);
//         return false;
//     }

//     // Convert from BGRA to BGR
//     cv::Mat bgrMat;
//     cv::cvtColor(mat, bgrMat, cv::COLOR_BGRA2BGR);

//     // Save the screenshot
//     bool success = cv::imwrite(filename, bgrMat);
//     if (!success) {
//         std::cerr << "Failed to save image" << std::endl;
//     }

//     // Clean up
//     SelectObject(hMemoryDC, hOldBitmap);
//     DeleteObject(hBitmap);
//     DeleteDC(hMemoryDC);
//     ReleaseDC(NULL, hScreenDC);

//     return success;
// }
void sendFile(SOCKET clientSocket, const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    // Get file size
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

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

    // Send end-of-file signal
    std::string endSignal = "FileEnd";
    send(clientSocket, endSignal.c_str(), endSignal.size(), 0);

    file.close();
    std::cout << "File sent successfully. Total bytes sent: " << totalSent << std::endl;
}
void startWebcam();
void stopWebcam();