#include <iostream>

#include "headers.h"
#include "fileEncryptor.h"

bool FileEncryptor::setDisk(std::string disk) {
	_disk = disk;
#if DEBUG
	std::clog << "0x" << &_disk << " Allocated Buffer :  _username  " << _disk << std::endl;
#endif
	return true;
}

bool FileEncryptor::setAesKey(std::string aesKey) {
	_aesKey = aesKey;
	#if DEBUG
	std::clog << "0x" << &_aesKey << " Allocated Buffer :  _username  " << _aesKey << std::endl;
	#endif
	return true;
}

bool FileEncryptor::setRsaKey(std::string rsaKey) {
	_rsaKey = rsaKey;
	#if DEBUG
	std::clog << "0x" << &_rsaKey << " Allocated Buffer :  _username  " << _rsaKey << std::endl;
	#endif
	return true;
}


FileEncryptor::FileEncryptor(std::string disk, std::string aesKey, std::string rsaKey) {
	setDisk(disk);
	setAesKey(aesKey);
	setRsaKey(rsaKey);



}