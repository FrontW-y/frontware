#include "systeme.h"
#include <iostream>
#include <thread>
#include "headers.h"

int main(void) {

	HANDLE hMutex = CreateMutex(NULL, TRUE, L"b29wc2llIHRoYXRzIHNhZCBmb3IgeW91IF5e=");
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return 1;
	}

	Systeme sys;
	std::cout << "Username : " << sys.getUsername() << std::endl;
	std::cout << "Computer Name : " << sys.getComputerName() << std::endl;
	std::cout << "CPU : " << sys.getCPU() << std::endl;
	std::cout << "HwId : " << sys.getHwId() << std::endl;
	std::cout << "LangId : " << sys.getLangId() << std::endl;
	std::cout << "OsVersion : " << sys.getOsVersion() << std::endl;


	
	return 0;
}