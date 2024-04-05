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

	std::string BuildRequestBody(const std::wstring& filePath, const std::string& postData, const std::string& boundary);

	

public:
	explicit Http(const std::wstring& userAgent);
	~Http();

	std::string GetResponseText();
	bool SendPostRequest(const std::wstring& serverName,const std::wstring& path,const std::wstring& headers,const std::string& postData);
	bool uploadFile(const std::wstring& serverName, const std::wstring& path, const std::wstring& headers, const std::wstring& filePath, std::string& responseData, const std::string& postData);
	bool downloadFile(const std::wstring& serverName, const std::wstring& path, const std::wstring& headers, const std::wstring& filePath);
	HRESULT checkInternetConnection();
};