#pragma once


#include <Windows.h>
#include <Lmcons.h>
#include <intrin.h>

#include <vector>


#include "headers.h"


class Systeme
{
private:

	char _username[USERNAME_LENGHT];
	char _computername[COMPUTER_NAME_LENGHT];
	char _CPUBrandString[CPU_INFO_LENGHT];

	DWORD drives;
	LANGID _langid;
	HW_PROFILE_INFO _hwProfileInfo;




public:

	char* getUsername();
	char* getComputerName();
	char* getCPU();

	bool setUsername();
	bool setComputerName();
	bool setCPU();





};
