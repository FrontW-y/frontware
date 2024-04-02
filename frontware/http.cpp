#include "http.h"
#include <iostream>

Http::Http(const std::wstring& userAgent) : hSession(WinHttpOpen(userAgent.c_str(), 
	WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
	WINHTTP_NO_PROXY_NAME,
	WINHTTP_NO_PROXY_BYPASS,
	0)),
hConnect(NULL), hRequest(NULL){}

Http::~Http() {
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
}

std::string Http::GetResponseText() {
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	BOOL  bResults = FALSE;
	DWORD dwSizeDownloaded;
	std::string output;
	do {
		dwSize = 0;
		if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
			std::cout << "Error " << GetLastError() << " in WinHttpQueryDataAvailable.\n";
		}
		pszOutBuffer = new char[dwSize + 1];
		if (!pszOutBuffer) {
			dwSize = 0;
		}
		else {
			ZeroMemory(pszOutBuffer, dwSize + 1);
			if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
				std::cout << "Error " << GetLastError() << " in WinHttpReadData.\n";
			}
			else {
				output.append(pszOutBuffer, dwDownloaded);
			}
			delete[] pszOutBuffer;
		}
	} while (dwSize > 0);
	return output;
}

bool Http::SendPostRequest(const std::wstring& serverName, const std::wstring& path, const std::wstring& headers, const std::wstring& postData) {
	hConnect = WinHttpConnect(hSession, serverName.c_str(), INTERNET_DEFAULT_HTTP_PORT, 0);
	if (!hConnect) {
		std::cout << "Error " << GetLastError() << " in WinHttpConnect.\n";
		return false;
	}
	hRequest = WinHttpOpenRequest(hConnect, L"POST", path.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	if (!hRequest) {
		std::cout << "Error " << GetLastError() << " in WinHttpOpenRequest.\n";
		return false;
	}
	if (!WinHttpSendRequest(hRequest, headers.c_str(), headers.length(), (LPVOID)postData.c_str(), postData.length(), postData.length(), 0)) {
		std::cout << "Error " << GetLastError() << " in WinHttpSendRequest.\n";
		return false;
	}
	if (!WinHttpReceiveResponse(hRequest, NULL)) {
		std::cout << "Error " << GetLastError() << " in WinHttpReceiveResponse.\n";
		return false;
	}
	return true;
}

