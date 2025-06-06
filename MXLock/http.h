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
	bool SendPostRequest(const std::wstring& serverName,const std::wstring& path,const std::wstring& headers,const std::string& postData);
	bool uploadFile(const std::wstring& serverName, const std::wstring& path, const std::wstring& headers, const std::wstring& filePath, std::string& responseData);
	bool downloadFile(const std::wstring& serverName, const std::wstring& path, const std::wstring& headers, const std::wstring& filePath);
	static HRESULT checkInternetConnection();
};