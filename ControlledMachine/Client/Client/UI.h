#ifndef UI_H
#define UI_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <vector>
#include <string>
#include "GmailAPI.h"

class UI {
private:
    const std::vector<email>& mailList;
    Fl_Window* window;

    // Các thành phần UI
    Fl_Box* left_label;
    Fl_Box* email_box;
    Fl_Box* email_content_label;

    // Thêm các thành phần cho 3 email
    Fl_Text_Display* email_content_1; 
    Fl_Text_Buffer* email_buffer_1;

    Fl_Text_Display* email_content_2; 
    Fl_Text_Buffer* email_buffer_2;

    Fl_Text_Display* email_content_3; 
    Fl_Text_Buffer* email_buffer_3;

    Fl_Box* right_label;
    Fl_Box* server_ip_label;
    Fl_Input* ip_input;
    Fl_Box* message_label;
    Fl_Input* message_input;
    Fl_Box* client_list_label;
    Fl_Box* client_list; // Hiển thị danh sách client
    Fl_Button* send_button;

    // Hàm cập nhật nội dung 3 email
    void updateEmailBoxes();

    // Hàm callback cho nút gửi và UI
    static void updateUI(void* userdata);
    static void on_send_button_click(Fl_Widget* w, void* userdata);

public:
    UI(const std::vector<email>& mailList); // Constructor
    void update_client_list(const std::vector<std::string>& clients); // Cập nhật danh sách client
    void run(); // Chạy giao diện
};

#endif // UI_H