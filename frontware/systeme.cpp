#pragma warning(disable: 6386)
#pragma warning(disable: 6387)


#include "systeme.h"


bool Systeme::setUsername() {

	WCHAR buff[USERNAME_LENGHT];
	DWORD size = USERNAME_LENGHT; ;
	if (GetUserNameW(buff, &size)) {
		wcstombs_s(nullptr, _username, buff, _TRUNCATE);
#if DEBUG
		std::cerr << "0x" << &_username << " Allocated Buffer :  _username  " << _username << std::endl;
#endif
		return true;
	}
	else {
#if DEBUG
		std::cerr << "0x" << &_username << " Unallocated Buffer :  _username" << std::endl;
#endif
		return false;
	}
}

bool Systeme::setComputerName() {
	WCHAR buff[COMPUTER_NAME_LENGHT];
	DWORD size = USERNAME_LENGHT;
	if (GetComputerNameW(buff, &size)) {
		wcstombs_s(nullptr, _computername, buff, _TRUNCATE);
#if DEBUG
		std::clog << "0x" << &_computername << " Allocated Buffer :  _computername  " << _computername << std::endl;
#endif
		return true;
	}
	else {
#if DEBUG
		std::cerr << "0x" << &_computername << " Unallocated Buffer :  _computername" << std::endl;
#endif
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
#if DEBUG
		std::clog << "0x" << &_CPUBrandString << " Allocated Buffer :  _CPUBrandString  " << _CPUBrandString << std::endl;
#endif
		return true;
	}
	else {
#if DEBUG
		std::cerr << "0x" << &_CPUBrandString << " Unallocated Buffer :  _CPUBrandString" << std::endl;
#endif
		return false;
	}
}

bool Systeme::setHwId() {
	HW_PROFILE_INFO hwProfileInfo;
	if (GetCurrentHwProfileW(&hwProfileInfo)) {
		wcstombs_s(nullptr, _HwId, hwProfileInfo.szHwProfileGuid, _TRUNCATE);
#if DEBUG
		std::clog << "0x" << &_HwId << " Allocated Buffer :  _HwId " << _HwId << std::endl;
#endif
		return true;
	}
#if DEBUG
	std::cerr << "0x" << &_HwId << " Unallocated Buffer :  _HwId" << std::endl;
#endif
	return false;
}

bool Systeme::setLocalization() {
	const char* data;
	const char* baseUrl = "https://ipapi.co/";
	std::vector<const char*> endpoint = { "country_name", "city", "latlong", "region"};
	for(int i = 0; i < endpoint.size(); i++) {
		char buff[0x64 + 1];
		HRESULT hResult = URLDownloadToFileA(NULL, buff, TEMPFILE, 0, NULL);
	}
}

const char* Systeme::getLocalization() {
	return _dataLocalization;
}

char* Systeme::getHwId() {
	char* str = (char*)malloc(sizeof(HW_GUIDLEN));
	strcpy_s(str, HW_GUIDLEN, _HwId);
	return str;
}

char* Systeme::getUsername() {
	char* str = (char*)malloc(sizeof(USERNAME_LENGHT));
	strcpy_s(str, USERNAME_LENGHT, _username);
	return str;
}

char* Systeme::getComputerName() {
	char* str = (char*)malloc(COMPUTER_NAME_LENGHT);
	strcpy_s(str, COMPUTER_NAME_LENGHT, _computername);
	return str;
}

char* Systeme::getCPU() {
	char* str = (char*)malloc(CPU_INFO_LENGHT);
	strcpy_s(str, CPU_INFO_LENGHT, _CPUBrandString);
	return str;
}

Systeme::Systeme() {
	setUsername();
	setCPU();
	setComputerName();
	setHwId();
}


