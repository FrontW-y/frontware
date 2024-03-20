#include "diskencryptor.h"
#include <iostream>
#include <Windows.h>

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

DiskEncryptor::DiskEncryptor(std::string disk)
{
	setDisk(disk);
	setFreeSpace();

}

DiskEncryptor::~DiskEncryptor()
{
	//delete _disk;
}