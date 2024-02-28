#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <Lmcons.h>
#include <intrin.h>
#endif


class Systeme
{
private:
	char* _username[UNLEN+1];
	char* _computername[CNLEN+1];
	LANGID _langid;



};
