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
cmake -G "MinGW Makefiles" ..

:: Biên dịch dự án với make
mingw32-make

:: Hoàn tất
echo Build process complete.
pause
