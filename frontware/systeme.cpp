#pragma warning(disable: 6386)
#pragma warning(disable: 6387)
#pragma comment(lib, "urlmon.lib")
#define TEMPFILE "LclTmp"

#include <iostream>
#include <fstream>
#include <Lmcons.h>
#include <intrin.h>


#include "systeme.h"
#include "headers.h"


bool Systeme::setUsername() {

	WCHAR buff[USERNAME_LENGHT];
	DWORD size = USERNAME_LENGHT; ;
	if (GetUserNameW(buff, &size)) {
		wcstombs_s(nullptr, _username, buff, _TRUNCATE);
		return true;
	}
	else {
		return false;
	}
}

bool Systeme::setComputerName() {
	WCHAR buff[COMPUTER_NAME_LENGHT];
	DWORD size = USERNAME_LENGHT;
	if (GetComputerNameW(buff, &size)) {
		wcstombs_s(nullptr, _computername, buff, _TRUNCATE);
		return true;
	}
	else {
		return false;
	}
}

bool Systeme::setCPU() {
	int CPUInfo[4] = { -1 };
	unsigned   nExIds, i = 0;
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];

	for (i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		if (i == 0x80000002) {
			memcpy_s(_CPUBrandString, sizeof(_CPUBrandString), CPUInfo, sizeof(CPUInfo));
		}
		else if (i == 0x80000003) {
			memcpy_s(_CPUBrandString + 16, sizeof(_CPUBrandString), CPUInfo, sizeof(CPUInfo));
		}
		else if (i == 0x80000004) {
			memcpy_s(_CPUBrandString + 32, sizeof(_CPUBrandString), CPUInfo, sizeof(CPUInfo));
		}
	}
	if (_CPUBrandString) {
		return true;
	}
	else {
		return false;
	}
}

bool Systeme::setHwId() {
	HW_PROFILE_INFO hwProfileInfo;
	if (GetCurrentHwProfileW(&hwProfileInfo)) {
		wcstombs_s(nullptr, _HwId, hwProfileInfo.szHwProfileGuid, _TRUNCATE);
		return true;
	}
	return false;
}

bool Systeme::setLocalization() {
	const char* baseUrl = "https://ipapi.co/";
	std::vector<const char*> endpoints = { "country_name", "city", "latlong", "region" };
	for (int i = 0; i < endpoints.size(); i++) {
		char buff[0x64];
		strcpy_s(buff, baseUrl);
		strcat_s(buff, endpoints[i]);
		if (URLDownloadToFileA(NULL, buff, TEMPFILE, 0, NULL) == S_OK) {
			std::ifstream file(TEMPFILE);
			if (file.is_open()) {
				std::string line;
				file.getline(buff, 0x64);
				_dataLocalization[i] = buff;
				file.close();
			}
			DeleteFileA(TEMPFILE);
		}
		else {
			return false;
		}
	}
	return true;
}

bool Systeme::setlangId() {
	_langId = GetUserDefaultUILanguage();
	return true;
}

bool Systeme::setDrives() {
	char* lDrives = new char[MAX_PATH];
	if (lDrives == nullptr) {
		return false; 
	}
	if (GetLogicalDriveStringsA(MAX_PATH, lDrives)) {
		for (char* drive = lDrives; *drive != '\0'; drive += 4) {
			_drives.push_back(std::string(drive, drive + 3));
		}
		delete[] lDrives;
		return true;
	}
	delete[] lDrives;
	return false;
}

void Systeme::setOsVersion() {
	if (IsWindows10OrGreater) {
		_osVersion = WIN_10;
	}
	else if (IsWindows8Point1OrGreater) {
		_osVersion = WIN_8_1;
	}
	else if (IsWindows8OrGreater) {
		_osVersion = WIN_8;
	}
	else if (IsWindows7OrGreater) {
		_osVersion = WIN_7;
	}
	else if (IsWindowsVistaOrGreater) {
		_osVersion = WIN_VISTA;
	}
	else if (IsWindowsXPOrGreater) {
		_osVersion = WIN_XP;
	}
	else if (IsWindowsServer) {
		_osVersion = WIN_SERV;
	}
	
	else {
		_osVersion = WIN_VERSION_UNKNOWN;	
	}
}

LANGID Systeme::getLangId() {
	return _langId;
}

int Systeme::getOsVersion() {
	return _osVersion;
}

std::vector<std::string> Systeme::getDrives() {
	return _drives;
}

std::map<int, std::string> Systeme::getLocalization() {
	return _dataLocalization;
}

std::string Systeme::getHwId() {
	std::string str(_HwId);
	return str;
}

std::string Systeme::getUsername() {
	std::string str(_username);
	return str;
}

std::string Systeme::getComputerName() {
	std::string str(_computername);
	return str;
}

std::string Systeme::getCPU() {
	std::string str(_CPUBrandString);	
	return str;
}


Systeme::Systeme() {
	setUsername();
	setDrives();
	setCPU();
	setlangId();
	setComputerName();
	setHwId();
	setLocalization();
	setOsVersion();
}