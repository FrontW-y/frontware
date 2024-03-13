#pragma once

#include <Windows.h>
#include <VersionHelpers.h>

#include <string>
#include <vector>
#include <map>

#define USERNAME_LENGHT 0x101
#define COMPUTER_NAME_LENGHT 0x101
#define CPU_INFO_LENGHT 0x40
#define HW_GUIDLEN 0x27


class Systeme
{

private:

	enum osVersion {
		WIN_95 = 0x01,
		WIN_98 = 0x02,
		WIN_ME = 0x03,
		WIN_NT = 0x04,
		WIN_2000 = 0x05,
		WIN_XP = 0x06,
		WIN_2003 = 0x07,
		WIN_VISTA = 0x08,
		WIN_7 = 0x09,
		WIN_8 = 0x0A,
		WIN_8_1 = 0x0B,
		WIN_10 = 0x0C,
		WIN_11 = 0x0D,
		WIN_SERV = 0x0E,
		WIN_VERSION_UNKNOWN = 0x0F
	};

	char _username[USERNAME_LENGHT];
	char _computername[COMPUTER_NAME_LENGHT];
	char _CPUBrandString[CPU_INFO_LENGHT];
	char _HwId[HW_GUIDLEN];

	osVersion _osVersion;
	std::vector<std::string> _drives;
	std::map<int, std::string> _dataLocalization;
	LANGID _langId;


public:

	Systeme();

	char* getUsername();
	char* getComputerName();
	char* getCPU();
	char* getHwId();
	LANGID getLangId();
	std::map<int, std::string> getLocalization();
	std::vector<std::string> getDrives();
	osVersion getOsVersion();
	 
	bool setLocalization();
	bool setUsername();
	bool setComputerName();
	bool setCPU();
	bool setHwId();
	bool setlangId();
	bool setDrives();
	void setOsVersion();

};
