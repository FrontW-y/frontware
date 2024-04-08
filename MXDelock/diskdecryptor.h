#pragma once

#include <string>

#include <cryptopp/ccm.h>
#include <cryptopp/aes.h>

class DiskDecryptor
{

private:

	std::string _disk;
	unsigned long _freespace;
	unsigned _numberOfFiles;
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption _d;

public:

	DiskDecryptor(std::string disk, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv);
	~DiskDecryptor();

	bool setDisk(std::string disk);
	bool setFreeSpace();
	bool setDecryption(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv);
	bool fileDecrypt(std::string file);

	void iterateFiles();


};
