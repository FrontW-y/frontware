#pragma once
#include <windows.h>
#include <winhttp.h>
#include <string>

#pragma comment(lib, "winhttp.lib")


class Http {

private:
	HINTERNET hSession;
	HINTERNET hConnect;
	HINTERNET hRequest;

public:
	explicit Http(const std::wstring& userAgent);
	~Http();

	std::string GetResponseText();
	bool SendPostRequest(const std::wstring& serverName,const std::wstring& path,const std::wstring& headers,const std::wstring& postData);



};