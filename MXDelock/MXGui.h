#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <string>

class MXGui {
private:
	Fl_PNG_Image* skull;
    Fl_Window* window;
    Fl_Box* label;
    Fl_Box* message;
    Fl_Box* pubKey;
    Fl_Box* time;
    Fl_Box* timeRemaining;
    int width;
    int height;

public:
    MXGui(const std::string& pubKey);
    void show();
    int run();
    void updateRemainingTime(const std::string& remainingTime);
    void setWidthHeight();
    ~MXGui();
};

