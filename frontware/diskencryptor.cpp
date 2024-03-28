#include "diskencryptor.h"

#include <iostream>
#include <Windows.h>
#include <cryptopp/ccm.h>

bool DiskEncryptor::setDisk(std::string disk)
{
	_disk = disk;
#if DEBUG
	std::clog << "0x" << &_disk << " Allocated Buffer :  _disk " << _disk << std::endl;
#endif

	return true;
}

bool DiskEncryptor::setFreeSpace()
{
	DWORD _sectorsPerCluster, _bytesPerSector, _numberOfFreeClusters, _totalNumberOfClusters;
	if (GetDiskFreeSpaceA(_disk.c_str(), &_sectorsPerCluster, &_bytesPerSector, &_numberOfFreeClusters, &_totalNumberOfClusters))
	{
		_freespace = (_sectorsPerCluster * _bytesPerSector * _numberOfFreeClusters);
#if DEBUG
		std::clog << "0x" << &_freespace << " Allocated Buffer :  _freespace " << _freespace << std::endl;
		#endif
		return true;
	}
	else
	{
#if DEBUG
		std::clog << "Error : " << GetLastError() << std::endl;
		#endif
		return false;
	}
}

DiskEncryptor::DiskEncryptor(std::string disk, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
{
	setDisk(disk);
	setFreeSpace();

	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
#if DEBUG
	std::clog << "0x" << &e << " Allocated Buffer :  e " << std::endl;
	std::clog << "sizeof(key) : " << key.size() << std::endl;
#endif


	e.SetKeyWithIV(key.data(), sizeof(key), iv.data(), sizeof(iv));
#if DEBUG
	std::clog << "0x" << &e << " Allocated Buffer :  e " << std::endl;
	std::clog << "sizeof(key) : " << sizeof(key) << std::endl;
	#endif

}

DiskEncryptor::~DiskEncryptor()
{
	//delete _disk;
}