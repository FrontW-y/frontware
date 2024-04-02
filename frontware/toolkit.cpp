#include "toolkit.h"
#include <codecvt>
#include <locale>
#include <Windows.h>
std::wstring to_wstring(const std::string& str)
{
    int required = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str.data(), str.size(), NULL, 0);
    std::wstring result;
    result.resize(required);
    int converted = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str.data(), str.size(), &result[0], result.size());
    return result;

}
