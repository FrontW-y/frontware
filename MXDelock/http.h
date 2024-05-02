#pragma once
#include <windows.h>
#include <winhttp.h>
#include <string>

#pragma comment(lib, "winhttp.lib")


class Http {

private:
	HINTERNET _hSession;
	HINTERNET _hConnect;
	HINTERNET _hRequest;




public:
	explicit Http(const std::wstring& userAgent);
	~Http();

	std::string GetResponseText();
	std::string SendPostRequest(const std::wstring& serverName, const std::wstring& path, const std::wstring& headers, const std::string& postData);
	static HRESULT checkInternetConnection();
};