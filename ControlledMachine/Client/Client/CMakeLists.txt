cmake_minimum_required(VERSION 3.10)

# Đặt tên dự án
project(ClientProject)

# Cài đặt chuẩn C++ (nếu cần thiết)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force static linking
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

# Thêm thư mục chứa các file header của FLTK
set(FLTK_DIR "C:/Users/HP/source/repos/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/build")

# Các file nguồn của dự án
set(SOURCES
    Client.cpp
    jsoncpp.cpp
    EmailMonitor.cpp
    GmailAPI.cpp
    GoogleDriveAPI.cpp
    GoogleOAuth.cpp
    UI.cpp
)

# Tạo file thực thi cho cả ứng dụng FLTK và Client
add_executable(client ${SOURCES})

# Thêm thư mục chứa các file header của libcurl và FLTK
target_include_directories(client PRIVATE 
    ${FLTK_DIR}
    ${FLTK_DIR}/.. 
    "./lib/curl/include"
)

# Thêm thư mục chứa các file thư viện của libcurl và FLTK
target_link_directories(client PRIVATE
    ${FLTK_DIR}/lib
    "./lib/curl/lib"
)

# Liên kết thư viện FLTK và các thư viện cần thiết khác
target_link_libraries(client PRIVATE
    ${FLTK_DIR}/lib/libfltk.a
    ${FLTK_DIR}/lib/libfltk_forms.a
    ${FLTK_DIR}/lib/libfltk_images.a
    ${FLTK_DIR}/lib/libfltk_gl.a
    curl
    ws2_32
    -lgdiplus
    -lgdi32
    -luser32
    -lshell32
    -lole32
    -luuid
    -lcomdlg32
    -ladvapi32
    -loleaut32
    -lcomctl32
)

# Định nghĩa các macro cần thiết
target_compile_definitions(client PRIVATE
    WIN32
    _WINDOWS
    _CRT_SECURE_NO_WARNINGS
    FL_LIBRARY
)
