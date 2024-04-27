#include <thread>
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <thread>

#include <cryptopp/filters.h>
#include <cryptopp/files.h>

#include "diskdecryptor.h"

#define FILE_EXTENSION ".locked"
#define DEFAULT_THREADS 1

bool DiskDecryptor::setDisk(std::string disk)
{
	_disk = disk;
	return true;
}

bool DiskDecryptor::setFreeSpace()
{
	DWORD _sectorsPerCluster, _bytesPerSector, _numberOfFreeClusters, _totalNumberOfClusters;
	if (GetDiskFreeSpaceA(_disk.c_str(), &_sectorsPerCluster, &_bytesPerSector, &_numberOfFreeClusters, &_totalNumberOfClusters))
	{
		_freespace = (_sectorsPerCluster * _bytesPerSector * _numberOfFreeClusters);
		return true;
	}
	return false;
}

bool DiskDecryptor::setDecryption(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
{
	_d.SetKeyWithIV(key.data(), key.size(), iv.data(), iv.size());
	return true;
}

void DiskDecryptor::iterateFiles() {
	std::vector<std::thread> threads;
	for (auto& entry : std::filesystem::recursive_directory_iterator(_disk, std::filesystem::directory_options::skip_permission_denied)) {
		try {
			if (entry.is_directory()) {
				
			}
			else {
				std::string ext = entry.path().extension().string();
				if (ext == FILE_EXTENSION) {
					if (_freespace < entry.file_size()) {
						break;
					}
					if (threads.size() > DEFAULT_THREADS) {
						for (std::thread& t : threads) {
							t.join();
						}
						threads.clear();
					}
					threads.push_back(std::thread(&DiskDecryptor::fileDecrypt, this, entry.path().string()));
				}
			}
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
	for (std::thread& t : threads) {
		t.join();
	}
}

bool DiskDecryptor::fileDecrypt(std::string file) {
	std::string output = file.substr(0, file.size() - 7);
	std::ifstream in(file, std::ios::binary);
	std::ofstream out(output, std::ios::binary);
	CryptoPP::FileSource fs(in, true, new CryptoPP::StreamTransformationFilter(_d, new CryptoPP::FileSink(out)));
	in.close();
	out.close();
	return true;
}

DiskDecryptor::DiskDecryptor(std::string disk, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
{
	_disk = disk;
	_freespace = 0;
	_numberOfFiles = 0;
	_d.SetKeyWithIV(key.data(), key.size(), iv.data(), iv.size());
}


DiskDecryptor::~DiskDecryptor()
{
}