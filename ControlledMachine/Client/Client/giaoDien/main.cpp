#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

void on_button_click(Fl_Widget* widget, void* userdata) {
    Fl_Button* button = (Fl_Button*)widget;
    button->label("Clicked!");
}

int main() {
    Fl_Window* window = new Fl_Window(400, 300, "FLTK Example");
    Fl_Button* button = new Fl_Button(150, 100, 100, 40, "Hello");
    button->callback(on_button_click);

    window->end();
    window->show();
    return Fl::run();
}
