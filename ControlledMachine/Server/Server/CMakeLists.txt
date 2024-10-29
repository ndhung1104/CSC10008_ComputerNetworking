cmake_minimum_required(VERSION 3.0)
project(YourProject)

find_package(OpenCV REQUIRED)
add_executable(test test.cpp WebcamRecorder.cpp)
target_link_libraries(test PRIVATE ${OpenCV_LIBS})