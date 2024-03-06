#include "systeme.h"



bool Systeme::setUsername() {

		WCHAR buff[USERNAME_LENGHT];
		if (GetUserNameW(buff, (LPDWORD)USERNAME_LENGHT)) {
			wcstombs_s(nullptr, _username, buff, _TRUNCATE);
			return true;
		}
		else {
			return false;
		}
}

bool Systeme::setComputerName() {
	WCHAR buff[COMPUTER_NAME_LENGHT];
	if (GetComputerNameW(buff, (LPDWORD)COMPUTER_NAME_LENGHT)) {
		wcstombs_s(nullptr, _username, buff, _TRUNCATE);
		return true;
	}
	else {
		return false;
	}
}

bool Systeme::setCPU() {
//implementing set cpu
}

char* Systeme::getUsername() {
	return _username;
}

char* Systeme::getComputerName() {
	return _computername;
}

char* Systeme::getCPU() {
	return _CPUBrandString;
}



