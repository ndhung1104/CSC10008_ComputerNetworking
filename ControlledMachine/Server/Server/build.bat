@echo off
:: Xóa nội dung thư mục build nếu đã tồn tại
if exist build (
    echo Deleting old build directory contents...
    rmdir /s /q build
)

:: Tạo lại thư mục build
mkdir build

:: Chuyển vào thư mục build
cd build

:: Chạy CMake để tạo cấu hình
cmake .. -DCMAKE_PREFIX_PATH=D:/Project/lib/vcpkg-master/vcpkg-master/installed/x64-windows -DCMAKE_BUILD_TYPE=Release -DCMAKE_CONFIGURATION_TYPES=Release

:: Biên dịch dự án với make
cmake --build . --config Release

:: Hoàn tất
echo Build process complete.
pause
