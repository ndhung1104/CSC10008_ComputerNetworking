#include "WebcamRecorder.h"

WebcamRecorder::WebcamRecorder(const std::string& outputPath) 
    : outputPath(outputPath), isRecording(false), recordingThread(nullptr) {
    // Open the default camera (usually the first one)
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open webcam." << std::endl;
        throw std::runtime_error("Webcam not available.");
    }
}

void WebcamRecorder::startRecording() {
    if (isRecording) {
        std::cout << "Recording is already in progress." << std::endl;
        return;
    }

    // Get frame width and height
    int frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Define the codec and create VideoWriter object
    writer.open(outputPath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frameWidth, frameHeight));

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open the output video file for writing." << std::endl;
        return;
    }

    isRecording = true;
    std::cout << "Recording started." << std::endl;

    // Start recording in a separate thread
    recordingThread = std::make_unique<std::thread>([this]() {
        recordingLoop();
    });
}

void WebcamRecorder::stopRecording() {
    if (!isRecording) {
        std::cout << "Recording is not in progress." << std::endl;
        return;
    }

    isRecording = false;
    
    // Wait for recording thread to finish
    if (recordingThread && recordingThread->joinable()) {
        recordingThread->join();
    }

    writer.release();
    cv::destroyAllWindows();
    std::cout << "Recording stopped and video saved to: " << outputPath << std::endl;
}

WebcamRecorder::~WebcamRecorder() {
    if (isRecording) {
        stopRecording();
    }
    if (cap.isOpened()) {
        cap.release();
    }
}

bool WebcamRecorder::screenShot(const std::string& filename) {
    // Get the device context of the screen
    HDC hScreenDC = GetDC(NULL);
    if (!hScreenDC) {
        std::cerr << "Failed to get screen DC" << std::endl;
        return false;
    }

    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    if (!hMemoryDC) {
        ReleaseDC(NULL, hScreenDC);
        std::cerr << "Failed to create compatible DC" << std::endl;
        return false;
    }

    // Get the dimensions of the screen
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    // Create a bitmap to hold the screenshot
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    if (!hBitmap) {
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
        std::cerr << "Failed to create bitmap" << std::endl;
        return false;
    }

    // Select the bitmap into the memory device context
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    // Print dimensions for debugging
    std::cout << "Screen dimensions: " << width << "x" << height << std::endl;

    // Bit block transfer into the memory device context
    if (!BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY)) {
        std::cerr << "BitBlt failed" << std::endl;
        SelectObject(hMemoryDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
        return false;
    }

    // Create bitmap info structure
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // Negative height to ensure correct orientation
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // Create OpenCV Mat
    cv::Mat mat(height, width, CV_8UC4);

    // Get the bitmap bits
    if (!GetDIBits(hMemoryDC, hBitmap, 0, height, mat.data,
                   (BITMAPINFO*)&bi, DIB_RGB_COLORS)) {
        std::cerr << "GetDIBits failed" << std::endl;
        SelectObject(hMemoryDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
        return false;
    }

    // Convert from BGRA to BGR
    cv::Mat bgrMat;
    cv::cvtColor(mat, bgrMat, cv::COLOR_BGRA2BGR);

    // Save the screenshot
    bool success = cv::imwrite(filename, bgrMat);
    if (!success) {
        std::cerr << "Failed to save image" << std::endl;
    }

    // Clean up
    SelectObject(hMemoryDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    return success;
}


    void WebcamRecorder::recordingLoop() {
        cv::Mat frame;
        while (isRecording) {
            cap >> frame; // Capture a new frame
            if (frame.empty()) {
                std::cerr << "Error: Captured empty frame." << std::endl;
                break;
            }
            writer.write(frame); // Write the frame to the video file
            cv::imshow("Webcam", frame); // Display the frame

            // Check for 'q' key press (optional - you can remove this if you only want external control)
            char key = cv::waitKey(1);
            if (key == 'q') {
                isRecording = false;
                break;
            }
        }
    }


// int main() {
//     std::string outputFilePath = "output.avi";

//     try {
//         WebcamRecorder recorder(outputFilePath);
        
//         // Start recording
//         recorder.startRecording();
        
//         // Wait for 10 seconds
//         std::cout << "Recording for 10 seconds..." << std::endl;
//         std::this_thread::sleep_for(std::chrono::seconds(10));
        
//         // Stop recording
//         std::cout << "Stopping recording..." << std::endl;
//         recorder.stopRecording();
        
//     } catch (const std::exception& e) {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }

//     return 0;
// }