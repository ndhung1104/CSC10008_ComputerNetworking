@echo off
:: Xóa nội dung thư mục build nếu đã tồn tại
:: Chuyển vào thư mục build
cd build

:: Biên dịch dự án với make
mingw32-make

:: Hoàn tất
echo Compile process complete.
pause
