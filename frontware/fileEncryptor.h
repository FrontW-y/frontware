#include <string>


#pragma comment(lib, "crypt32.lib")

class FileEncryptor
{

private:
	std::string _disk;
	std::string _rsaKey;
	std::string _aesKey;

public:

	FileEncryptor(std::string disk, std::string aesKey, std::string rsaKey);
	~FileEncryptor();

	bool aesEncryptFile(const char* file, std::string& aesKey);
	bool rsaEncryptFile(const char* file, std::string& rsaKey);

	bool setRsaKey(std::string rsaKey);
	bool setAesKey(std::string aesKey);
	bool setDisk(std::string disk);
	

};