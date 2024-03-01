#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <Lmcons.h>
#include <intrin.h>
#endif

#include "headers.h"


class Systeme
{
private:

	char* _username[USERNAME_LENGHT];
	char* _computername[COMPUTER_NAME_LENGHT];
	char _CPUBrandString[CPU_INFO_LENGHT];

	LANGID _langid;
	HW_PROFILE_INFO _hwProfileInfo;



};
