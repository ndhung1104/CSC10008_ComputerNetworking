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
cmake .. -DCMAKE_PREFIX_PATH=D:/Project/lib/vcpkg-master/vcpkg-master/installed/x64-windows

:: Biên dịch dự án với make
cmake --build .

:: Hoàn tất
echo Build process complete.
pause
