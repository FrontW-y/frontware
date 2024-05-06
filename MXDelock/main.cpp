#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/FL_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <FL/fl_types.h>
#include <windows.h>
#include <FL/Fl_Input.H>
#include "http.h"
#include <iostream>
#include <time.h>
#include <thread>
#include "MXGui.h"





std::string hwId;

std::string setHwId() {
	HW_PROFILE_INFOA hwProfileInfo;
	ZeroMemory(&hwProfileInfo, sizeof(HW_PROFILE_INFOA));
	if (GetCurrentHwProfileA(&hwProfileInfo)) {
		return hwProfileInfo.szHwProfileGuid;
	}

	return "false";
}

void noAltF4() {
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
}

int main(int argc, char** argv)
{
	noAltF4();
	if (Http::checkInternetConnection() != S_OK) {
		return 1;
	}
	hwId = setHwId();
	Http http(L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");
	std::string clef = http.SendPostRequest(L"localhost", L"/server/hdhohzuag.php?action=getPublicKey", L"Content-Type: application/x-www-form-urlencoded\r\n", "uuid=" + hwId);
	MXGui Gui(clef);
	Gui.show();

	MXGui::isEnterPress();



	return Gui.run();
}



