#include "systeme.h"
#include <iostream>
#include <thread>
#include "headers.h"

int main(void) {

#if DEBUG
	std::cout << "DEBUG MODE" << std::endl;
#else
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

	HANDLE hMutex = CreateMutex(NULL, TRUE, L"b29wc2llIHRoYXRzIHNhZCBmb3IgeW91IF5e=");
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return 1;
	}



	Systeme sys;


	
	return 0;
}