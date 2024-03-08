#pragma once


#include <Windows.h>
#include <Lmcons.h>
#include <intrin.h>


#include <iostream>
#include <vector>


#include "headers.h"

#define USERNAME_LENGHT 0x101
#define COMPUTER_NAME_LENGHT 0x101
#define CPU_INFO_LENGHT 0x40
#define HW_GUIDLEN 0x27

#define TEMPFILE "LocalTmp"

class Systeme
{
private:

	char _username[USERNAME_LENGHT];
	char _computername[COMPUTER_NAME_LENGHT];
	char _CPUBrandString[CPU_INFO_LENGHT];
	char _HwId[HW_GUIDLEN];
	
	const char* _dataLocalization;

	DWORD drives;
	LANGID _langid;

public:

	Systeme();

	char* getUsername();
	char* getComputerName();
	char* getCPU();
	char* getHwId();
	const char* getLocalization();

	bool setLocalization();
	bool setUsername();
	bool setComputerName();
	bool setCPU();
	bool setHwId();

};
