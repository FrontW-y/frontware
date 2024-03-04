#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <Lmcons.h>
#include <intrin.h>
#endif

#include <vector>


#include "headers.h"


class Systeme
{
private:

	char* _username[USERNAME_LENGHT];
	char* _computername[COMPUTER_NAME_LENGHT];
	char _CPUBrandString[CPU_INFO_LENGHT];

#ifdef _WIN32
	DWORD drives;
	LANGID _langid;
	HW_PROFILE_INFO _hwProfileInfo;
#endif

#ifdef __linux__
	std::vector<std::string> drives;

#endif


public:

	char* getUsername();
	char* getComputerName();
	char getCPU();

	bool setUsername();
	bool setComputerName();
	bool setCPU();





};
