cmake_minimum_required(VERSION 3.0)
project(YourProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
add_executable(main Server.cpp Utility.cpp service.cpp WebcamRecorder.cpp)
target_link_libraries(main PRIVATE ws2_32 ole32 shell32 uuid ${OpenCV_LIBS})