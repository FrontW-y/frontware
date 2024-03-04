#pragma once

#include "systeme.h"

bool Systeme::setUsername() {
	try {
		LPWSTR buff;
		GetUserName(buff, (LPDWORD)USERNAME_LENGHT);
		this->_username = buff;
	}
}

char* Systeme::getUsername() {
	return this->_username;
}

