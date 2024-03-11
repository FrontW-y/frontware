#pragma once

#include <Windows.h>
#include <string>
#include <vector>

#define USERNAME_LENGHT 0x101
#define COMPUTER_NAME_LENGHT 0x101
#define CPU_INFO_LENGHT 0x40
#define HW_GUIDLEN 0x27


class Systeme
{
private:

	char _username[USERNAME_LENGHT];
	char _computername[COMPUTER_NAME_LENGHT];
	char _CPUBrandString[CPU_INFO_LENGHT];
	char _HwId[HW_GUIDLEN];
	std::vector<std::string> _drives;
	std::string _dataLocalization;
	LANGID _langId;

public:

	Systeme();

	char* getUsername();
	char* getComputerName();
	char* getCPU();
	char* getHwId();
	LANGID getLangId();
	std::string getLocalization();
	std::vector<std::string> getDrives();
	 
	bool setLocalization();
	bool setUsername();
	bool setComputerName();
	bool setCPU();
	bool setHwId();
	bool setlangId();
	bool setDrives();

};
