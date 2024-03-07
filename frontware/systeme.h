#pragma once


#include <Windows.h>
#include <Lmcons.h>
#include <intrin.h>


#include <iostream>
#include <vector>


#include "headers.h"

#define USERNAME_LENGHT 0x101
#define COMPUTER_NAME_LENGHT 0x101
#define CPU_INFO_LENGHT 0x101
#define HW_GUIDLEN 0x27

class Systeme
{
private:

	char _username[USERNAME_LENGHT];
	char _computername[COMPUTER_NAME_LENGHT];
	char _CPUBrandString[CPU_INFO_LENGHT];
	char _HwProfileGuid[HW_GUIDLEN];

	DWORD drives;
	LANGID _langid;

public:

	char* getUsername();
	char* getComputerName();
	char* getCPU();

	bool setUsername();
	bool setComputerName();
	bool setCPU();

};
