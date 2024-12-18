ĐỒ ÁN MÔN HỌC MẠNG MÁY TÍNH

VIẾT HỆ PHẦN MỀM ĐIỀU KHIỂN MÁY TÍNH TỪ XA DÙNG E-MAIL

Mô tả : Người dùng or Admin thực hiện các công việc điều khiển một máy tính nào đó trong LAN (định danh bằng IP address), như : Shutdown; Reset; Chụp màn hình; Keyloger; List/Start/Stop các apps. và processes ; Copy/Del files ; Start/Stop Webcam

Hệ phần mềm gồm có 2 module chính :

[1]. SERVER : chạy trên máy bị điều khiển, tiếp nhận những yêu cầu điều khiển gởi từ CLIENT, và thi hành những yêu cầu đó như : shutdown, reset, chụp màn hình, keyloger, list/start/stop apps …. rồi gởi kết quả về cho CLIENT.

[2]. CLIENT : thực hiện các công việc chính :

1. Check mail để nhận lệnh điều khiển từ user or admin

2. Dựa vào nội dung mail, gởi yêu cầu điều khiển đến SERVER

3. Gởi mail trả lời kết quả cho user or admin