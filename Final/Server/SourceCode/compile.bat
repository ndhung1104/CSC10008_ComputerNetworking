@echo off
:: Xóa nội dung thư mục build nếu đã tồn tại

:: Chuyển vào thư mục build
cd build



:: Biên dịch dự án với make
cmake --build .

:: Hoàn tất
echo Build process complete.
pause
