cmake_minimum_required(VERSION 3.16)
project(YourProject)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Set the vcpkg toolchain file

# # Set directories for OpenCV and Protobuf
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/lib/opencv4")

# # Find packages
# find_package(OpenCV REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} Server.cpp Utility.cpp service.cpp WebcamRecorder.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ws2_32 
    ole32 
    shell32 
    uuid 
    ${OpenCV_DIR}
)