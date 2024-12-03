cmake_minimum_required(VERSION 3.16)
project(YourProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Set the vcpkg toolchain file
# set(CMAKE_TOOLCHAIN_FILE "D:/Project/lib/vcpkg-master/vcpkg-master/scripts/buildsystems/vcpkg.cmake")

# # Set directories for OpenCV and Protobuf
set(OpenCV_DIR "C:/opencv/build")
# set(Protobuf_DIR "D:/Project/lib/vcpkg-master/vcpkg-master/installed/x64-windows/share/protobuf")

# # Explicitly set prefix path
# list(APPEND CMAKE_PREFIX_PATH 
#     "D:/Project/lib/vcpkg-master/vcpkg-master/installed/x64-windows"
#     "D:/Project/lib/vcpkg-master/vcpkg-master/installed/x64-windows/share"
# )

# # Find packages
# find_package(Protobuf REQUIRED)
find_package(OpenCV REQUIRED)

# Include directories
# include_directories(${OpenCV_INCLUDE_DIRS})
# include_directories(${Protobuf_INCLUDE_DIRS})

# Create executable
add_executable(${PROJECT_NAME} Server.cpp Utility.cpp service.cpp WebcamRecorder.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ws2_32 
    ole32 
    shell32 
    uuid 
    ${OpenCV_LIBS}
    # ${Protobuf_LIBRARIES}
)

# Optional: Print package information for debugging
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "Protobuf version: ${Protobuf_VERSION}")
message(STATUS "Protobuf libraries: ${Protobuf_LIBRARIES}")