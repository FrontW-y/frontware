#include <vector>
#include <iostream>
#include <netlistmgr.h>
#include <fstream>
#include <sstream>

#include "http.h"


Http::Http(const std::wstring& userAgent) : _hSession(WinHttpOpen(userAgent.c_str(),
	WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
	WINHTTP_NO_PROXY_NAME,
	WINHTTP_NO_PROXY_BYPASS,
	0)),
	_hConnect(NULL), _hRequest(NULL) {}

Http::~Http() {
	if (_hRequest) WinHttpCloseHandle(_hRequest);
	if (_hConnect) WinHttpCloseHandle(_hConnect);
	if (_hSession) WinHttpCloseHandle(_hSession);
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
		if (!WinHttpQueryDataAvailable(_hRequest, &dwSize)) {
			std::cout << "Error " << GetLastError() << " in WinHttpQueryDataAvailable.\n";
		}
		pszOutBuffer = new char[dwSize + 1];
		if (!pszOutBuffer) {
			dwSize = 0;
		}
		else {
			ZeroMemory(pszOutBuffer, dwSize + 1);
			if (!WinHttpReadData(_hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
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

std::string Http::SendPostRequest(const std::wstring& serverName, const std::wstring& path, const std::wstring& headers, const std::string& postData) {
	_hConnect = WinHttpConnect(_hSession, serverName.c_str(), INTERNET_DEFAULT_HTTP_PORT, 0);
	if (!_hConnect) {
		std::cout << "Error " << GetLastError() << " in WinHttpConnect.\n";
		return "falseUn";
	}
	_hRequest = WinHttpOpenRequest(_hConnect, L"POST", path.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	if (!_hRequest) {
		std::cout << "Error " << GetLastError() << " in WinHttpOpenRequest.\n";
		return "falseDeux";
	}
	std::cout << _hRequest;
	if (!WinHttpSendRequest(_hRequest, headers.c_str(), headers.length(), (LPVOID)postData.c_str(), postData.length(), postData.length(), 0)) {
		std::cout << "Error " << GetLastError() << " in WinHttpSendRequest.\n";
		return "falseTrois";
	}


	if (!WinHttpReceiveResponse(_hRequest, NULL)) {
		std::cout << "Error " << GetLastError() << " in WinHttpReceiveResponse.\n";
		return "falseQuatre";
	}
		 
return GetResponseText();
	
}






HRESULT Http::checkInternetConnection() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (SUCCEEDED(hr)) {
		INetworkListManager* pNetworkListManager = NULL;
		hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL, IID_INetworkListManager, (void**)&pNetworkListManager);
		if (SUCCEEDED(hr)) {
			NLM_CONNECTIVITY nlmConnectivity = NLM_CONNECTIVITY_DISCONNECTED;
			hr = pNetworkListManager->GetConnectivity(&nlmConnectivity);
			if (SUCCEEDED(hr)) {

			}
			pNetworkListManager->Release();
		}
		CoUninitialize();
	}
	return hr;
}