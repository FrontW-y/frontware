#include "systeme.h"



bool Systeme::setUsername() {

		WCHAR buff[USERNAME_LENGHT];
		DWORD size = USERNAME_LENGHT;	;
		if (GetUserNameW(buff, &size)) {
			wcstombs_s(nullptr, _username, buff, _TRUNCATE);
			return true;
		}
		else {
#if DEBUG
			std::cerr << "0x" << &_username << " Unallocated Buffer :  CPUINFO";
#endif
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
#if DEBUG
		std::cerr << "0x" << &_computername << " Unallocated Buffer :  CPUINFO";
#endif
		return false;
	}
}

bool Systeme::setCPU() {
	int cpu[4] = { -1 };
	unsigned nExtIds, i= 0;
	__cpuid(cpu, 0x80000000);
	nExtIds = cpu[0];
	for (i = 0x80000000; i <= nExtIds; i++) {
		__cpuid(cpu, i);
		if (i == 0x80000002) {
			memcpy(_CPUBrandString, cpu, sizeof(cpu));
			return true;
		}
		else if (i == 0x80000003) {
			memcpy(_CPUBrandString + 16, cpu, sizeof(cpu));
			return true;
		}
		else if (i == 0x80000004) {
			memcpy(_CPUBrandString + 32, cpu, sizeof(cpu));
		} 
#if DEBUG
		std::cerr << "0x" << &_CPUBrandString << " Unallocated Buffer :  CPUINFO";
#endif
		return false;
	}
	return true;
}	

char* Systeme::getUsername() {
	char* str = (char*)malloc(sizeof(USERNAME_LENGHT));
	strcpy_s(str, sizeof(str), _username);
	return str;
}

char* Systeme::getComputerName() {
	char* str = (char*)malloc(COMPUTER_NAME_LENGHT);
	strcpy_s(str, sizeof(str), _computername);
	return str;
}

char* Systeme::getCPU() {
	char* str = (char*)malloc(CPU_INFO_LENGHT * 200); 
	strcpy_s(str, sizeof(str), _CPUBrandString);
	return str;
}



