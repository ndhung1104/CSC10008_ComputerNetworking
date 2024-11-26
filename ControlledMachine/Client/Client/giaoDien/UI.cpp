#include <FL/Fl.H>
#include <FL/Fl_ask.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Scroll.H>
#include <string>

// Hàm xử lý khi nhấn nút "Gửi"
void on_send_button_click(Fl_Widget* w, void* userdata) {
    Fl_Input* ip_input = static_cast<Fl_Input*>(userdata);
    std::string message = "Gửi đến IP: " + std::string(ip_input->value());
    fl_message(message.c_str());
}

int main() {
    // Tạo cửa sổ chính
    Fl_Window* window = new Fl_Window(900, 600, "Gửi Thông Điệp đến Máy Chủ");

    // Nửa bên trái
    Fl_Box* left_label = new Fl_Box(20, 20, 400, 30, "Gmail của Bạn");
    left_label->labelfont(FL_BOLD);
    left_label->labelsize(16);

    Fl_Box* email_box = new Fl_Box(20, 60, 400, 30, "📧 example@gmail.com");
    email_box->box(FL_BORDER_BOX);
    email_box->color(FL_WHITE);

    Fl_Box* email_content_label = new Fl_Box(20, 110, 400, 30, "Nội dung Gmail được gửi đến");
    email_content_label->labelfont(FL_BOLD);
    email_content_label->labelsize(16);

    Fl_Text_Buffer* email_buffer = new Fl_Text_Buffer();
    Fl_Text_Display* email_content = new Fl_Text_Display(20, 150, 400, 200);
    email_content->buffer(email_buffer);
    email_buffer->text(
        "Người gửi: sender@example.com\n"
        "Chủ đề: Chủ đề email ở đây\n"
        "Nội dung: Nội dung email xuất hiện ở đây."
    );

    // Nửa bên phải
    Fl_Box* right_label = new Fl_Box(460, 20, 400, 30, "Thông Tin Client");
    right_label->labelfont(FL_BOLD);
    right_label->labelsize(16);

    Fl_Box* server_ip_label = new Fl_Box(460, 60, 400, 30, "Địa chỉ IP của Máy Chủ");
    Fl_Input* ip_input = new Fl_Input(460, 100, 400, 30, nullptr);
    ip_input->value("192.168.1.1");

    Fl_Box* message_label = new Fl_Box(460, 150, 400, 30, "Tin nhắn");
    Fl_Input* message_input = new Fl_Input(460, 190, 400, 30, nullptr);
    message_input->value("Thông điệp từ máy chủ");

    Fl_Box* client_list_label = new Fl_Box(460, 240, 400, 30, "Các Địa Chỉ IP Client Kết Nối");
    Fl_Box* client_list = new Fl_Box(460, 280, 400, 80,
        "192.168.1.2\n"
        "192.168.1.3\n"
        "192.168.1.4");
    client_list->box(FL_BORDER_BOX);
    client_list->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP_LEFT);

    Fl_Button* send_button = new Fl_Button(460, 380, 200, 40, "Gửi");
    send_button->callback(on_send_button_click, ip_input);

    // Kết thúc thiết kế
    window->end();
    window->show();

    return Fl::run();
}
