#include "UI.h"
#include <FL/Fl_Message.H>
#include <iostream>
#include <sstream>

void UI::sendMessage(std::string message, const SOCKET& clientSocket)
{
    int byteCount = send(clientSocket, message.c_str(), message.size(), 0);

    if (byteCount > 0) {
        std::cout << "Message sent: " << message <<  std::endl;
    }
    else {
        std::cout << "Failed to send message." <<  std::endl;
    }
}

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

void UI::updateSocketList(){
    std::vector<std::string> ipAddressList;
    struct sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);

    for (const SOCKET& socket : socketList) {
        // Get the peer (remote) address of the socket
        if (getpeername(socket, (struct sockaddr*)&addr, &addrLen) == 0) {
            char socketIP[INET_ADDRSTRLEN];

            // Convert the IP address from binary to text form
            inet_ntop(AF_INET, &addr.sin_addr, socketIP, INET_ADDRSTRLEN);
            std::string socketIPString(socketIP);
            ipAddressList.push_back(socketIPString);
        }
    }

    size_t ipCount = ipAddressList.size();

    // Hiển thị IP 1 (IP cuối cùng)
    if (ipCount >= 1) {
        ip_box_1->label(ipAddressList[ipCount - 1].c_str());
    } else {
        ip_box_1->label("Không có IP nào để hiển thị.");
    }

    // Hiển thị IP 2 (IP cuối - 1)
    if (ipCount >= 2) {
        ip_box_2->label(ipAddressList[ipCount - 2].c_str());
    } else {
        ip_box_2->label("Không có IP nào để hiển thị.");
    }

    // Hiển thị IP 3 (IP cuối - 2)
    if (ipCount >= 3) {
        ip_box_3->label(ipAddressList[ipCount - 3].c_str());
    } else {
        ip_box_3->label("Không có IP nào để hiển thị.");
    }

    // Yêu cầu vẽ lại giao diện
    ip_box_1->redraw();
    ip_box_2->redraw();
    ip_box_3->redraw();

}



// Constructor của lớp UI
UI::UI(const std::vector<email>& mailList, const std::vector<SOCKET>& socketList, const std::string& ip_address) : mailList(mailList), socketList(socketList), ip_address(ip_address) {
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
    ip_input->value(ip_address.c_str());

    message_label = new Fl_Box(460, 150, 400, 30, "Tin nhắn");
    message_input = new Fl_Input(460, 190, 400, 30, nullptr);
    message_input->value("Thông điệp từ máy chủ");

    client_list_label = new Fl_Box(460, 240, 400, 30, "Các Địa Chỉ IP Client Kết Nối");
    client_list_label->labelfont(FL_BOLD);
    client_list_label->labelsize(16);

    // Thêm các hộp hiển thị IP
    ip_box_1 = new Fl_Box(460, 280, 400, 30, "Không có IP nào để hiển thị.");
    ip_box_1->box(FL_BORDER_BOX);
    ip_box_1->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
    ip_box_1->labelfont(FL_BOLD);

    ip_box_2 = new Fl_Box(460, 320, 400, 30, "Không có IP nào để hiển thị.");
    ip_box_2->box(FL_BORDER_BOX);
    ip_box_2->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
    ip_box_2->labelfont(FL_BOLD);

    ip_box_3 = new Fl_Box(460, 360, 400, 30, "Không có IP nào để hiển thị.");
    ip_box_3->box(FL_BORDER_BOX);
    ip_box_3->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
    ip_box_3->labelfont(FL_BOLD);

    send_button = new Fl_Button(560, 420, 200, 40, "Gửi"); // Repositioned
    send_button->callback(on_send_button_click, this);

    window->end();
    window->show();
}


void UI::updateUI(void* userdata) {
    UI* ui = static_cast<UI*>(userdata);
    ui->updateEmailBoxes();
    ui->updateSocketList();
    Fl::repeat_timeout(0.2, updateUI, userdata); // Schedule next update
}


// Hàm callback khi nhấn nút Gửi
// void UI::on_send_button_click(Fl_Widget* w, void* userdata) {
//     Fl_Input* ip_input = static_cast<Fl_Input*>(userdata);
//     std::string message = std::string(ip_input->value());
//     for (const SOCKET& socket : socketList)
//         sendMessage(message, socket);
//     fl_message(message.c_str());
// }

void UI::on_send_button_click(Fl_Widget* w, void* userdata) {
    UI* ui = static_cast<UI*>(userdata); // Cast userdata về UI*
    std::string message = ui->message_input->value(); // Truy cập trường message_input trong UI

    if (message.empty()) {
        fl_message("Message cannot be empty!");
        return;
    }

    if (ui->socketList.empty()) {
        fl_message("No connected clients to send the message.");
        return;
    }

    // Gửi thông điệp đến tất cả client trong socketList
    for (const SOCKET& socket : ui->socketList) {
        ui->sendMessage(message, socket);
    }

    fl_message(("Message sent to all clients: " + message).c_str());
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
