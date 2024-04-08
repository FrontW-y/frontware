#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include "static.h"
#include <FL/Fl_Image.H>



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	Fl_RGB_Image* gifImage = new Fl_RGB_Image(rawData, 256, 256, 5);

	Fl_Window* window = new Fl_Window(340, 180, "ddddd");
	window->fullscreen();	
	Fl_Box* box = new Fl_Box(50, 50, 200, 100);
	box->image(gifImage);
	window->end();
	window->show();
	return Fl::run();
}