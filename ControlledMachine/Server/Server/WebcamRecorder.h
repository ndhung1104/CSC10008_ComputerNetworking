#ifndef WEBCAMRECORDER 
#define WEBCAMRECORDER

#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <atomic>
#include <memory>

class WebcamRecorder {
public:
    WebcamRecorder(const std::string& outputPath);

    void startRecording();

    void stopRecording();

    ~WebcamRecorder();

private:
    void recordingLoop();

    cv::VideoCapture cap;     // To capture video from the webcam
    cv::VideoWriter writer;   // To write video to a file
    std::string outputPath;   // Output path for the video file
    std::atomic<bool> isRecording;  // Flag to track recording status
    std::unique_ptr<std::thread> recordingThread; // Thread for recording
};

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

#endif