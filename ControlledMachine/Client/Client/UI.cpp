#include "UI.h"
#include <FL/Fl_Message.H>
#include <iostream>
#include <sstream>

void UI::updateEmailBoxes() {
    // Kiểm tra số lượng email có sẵn trong danh sách
    size_t emailCount = mailList.size();

    // Email cuối cùng
    if (emailCount >= 1) {
        const auto& email1 = mailList[emailCount - 1];
        std::string emailText1 = "Người gửi: " + email1.sender + "\n" +
                                 "Chủ đề: " + email1.subject + "\n" +
                                 "Nội dung: " + email1.body;
        email_buffer_1->text(emailText1.c_str());
    } else {
        email_buffer_1->text("Không có email nào để hiển thị.");
    }

    // Email thứ 2 từ cuối
    if (emailCount >= 2) {
        const auto& email2 = mailList[emailCount - 2];
        std::string emailText2 = "Người gửi: " + email2.sender + "\n" +
                                 "Chủ đề: " + email2.subject + "\n" +
                                 "Nội dung: " + email2.body;
        email_buffer_2->text(emailText2.c_str());
    } else {
        email_buffer_2->text("Không có email nào để hiển thị.");
    }

    // Email thứ 3 từ cuối
    if (emailCount >= 3) {
        const auto& email3 = mailList[emailCount - 3];
        std::string emailText3 = "Người gửi: " + email3.sender + "\n" +
                                 "Chủ đề: " + email3.subject + "\n" +
                                 "Nội dung: " + email3.body;
        email_buffer_3->text(emailText3.c_str());
    } else {
        email_buffer_3->text("Không có email nào để hiển thị.");
    }

    // Yêu cầu vẽ lại các hộp hiển thị email
    email_content_1->redraw();
    email_content_2->redraw();
    email_content_3->redraw();
}



// Constructor của lớp UI
UI::UI(const std::vector<email>& mailList) : mailList(mailList) {
    window = new Fl_Window(900, 600, "Gửi Thông Điệp đến Máy Chủ");

    // Nửa bên trái
    left_label = new Fl_Box(20, 20, 400, 30, "Gmail của Bạn");
    left_label->labelfont(FL_BOLD);
    left_label->labelsize(16);

    email_box = new Fl_Box(20, 60, 400, 30, "📧 example@gmail.com");
    email_box->box(FL_BORDER_BOX);
    email_box->color(FL_WHITE);

    email_content_label = new Fl_Box(20, 110, 400, 30, "Nội dung Gmail được gửi đến");
    email_content_label->labelfont(FL_BOLD);
    email_content_label->labelsize(16);

    // Tạo 3 buffer và display cho 3 email
    email_buffer_1 = new Fl_Text_Buffer();
    email_content_1 = new Fl_Text_Display(20, 150, 400, 100); // Email 1
    email_content_1->buffer(email_buffer_1);

    email_buffer_2 = new Fl_Text_Buffer();
    email_content_2 = new Fl_Text_Display(20, 260, 400, 100); // Email 2
    email_content_2->buffer(email_buffer_2);

    email_buffer_3 = new Fl_Text_Buffer();
    email_content_3 = new Fl_Text_Display(20, 370, 400, 100); // Email 3
    email_content_3->buffer(email_buffer_3);

    if (!mailList.empty()) {
        updateEmailBoxes();
    }

    // Nửa bên phải
    right_label = new Fl_Box(460, 20, 400, 30, "Thông Tin Client");
    right_label->labelfont(FL_BOLD);
    right_label->labelsize(16);

    server_ip_label = new Fl_Box(460, 60, 400, 30, "Địa chỉ IP của Máy Chủ");
    ip_input = new Fl_Input(460, 100, 400, 30, nullptr);
    ip_input->value("192.168.1.1");

    message_label = new Fl_Box(460, 150, 400, 30, "Tin nhắn");
    message_input = new Fl_Input(460, 190, 400, 30, nullptr);
    message_input->value("Thông điệp từ máy chủ");

    client_list_label = new Fl_Box(460, 240, 400, 30, "Các Địa Chỉ IP Client Kết Nối");
    client_list = new Fl_Box(460, 280, 400, 80, "");
    client_list->box(FL_BORDER_BOX);
    client_list->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP_LEFT);

    send_button = new Fl_Button(460, 380, 200, 40, "Gửi");
    send_button->callback(on_send_button_click, ip_input);

    window->end();
    window->show();
}


void UI::updateUI(void* userdata) {
    UI* ui = static_cast<UI*>(userdata);
    ui->updateEmailBoxes();
    Fl::repeat_timeout(0.2, updateUI, userdata); // Schedule next update
}


// Hàm callback khi nhấn nút Gửi
void UI::on_send_button_click(Fl_Widget* w, void* userdata) {
    Fl_Input* ip_input = static_cast<Fl_Input*>(userdata);
    std::string message = "Gửi đến IP: " + std::string(ip_input->value());
    fl_message(message.c_str());
}

// Cập nhật danh sách client từ vector
void UI::update_client_list(const std::vector<std::string>& clients) {
    std::ostringstream oss;
    for (const auto& client : clients) {
        oss << client << "\n";
    }
    client_list->label(oss.str().c_str()); // Cập nhật nội dung
    client_list->redraw(); // Yêu cầu vẽ lại
}

// Phương thức chạy giao diện người dùng
void UI::run() {
    Fl::add_timeout(0.2, updateUI, this);
    Fl::run();
}
