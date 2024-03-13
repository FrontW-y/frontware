#include <string>


#pragma comment(lib, "crypt32.lib")

class FileEncryptor
{

private:
	std::string _disk;
	std::string _rsaKey;
	std::string _aesKey;

public:
	FileEncryptor(std::string disks);
	~FileEncryptor();

	bool EncryptFile(const char* file, const char* password);

};