#ifndef DEBUG_HPP
#define DEBUG_HPP
#include "lang.hpp"

FILE* DebugFilePointer;
bool DebugLogEnabled = false;

bool InitDebug()
{
	#ifdef _DEBUG
	DebugFilePointer = fopen("rsd_debug.log", "a");
	if (DebugFilePointer == NULL)
		return false;
	DebugLogEnabled = true;
	#endif
	return true;
}

bool DebugWriteLog(LPCWSTR message)
{
	if (!DebugLogEnabled)
		return false;
	SYSTEMTIME t;
	GetSystemTime(&t);
	wstring time_str = L"[";
	wstring tmp_str;
	wstringstream converter;
	converter << t.wYear;
	converter >> tmp_str;
	time_str += tmp_str;
	time_str += L'/';
	converter << t.wMonth;
	converter >> tmp_str;
	time_str += tmp_str;
	time_str += L'/';
	converter << t.wDay;
	converter >> tmp_str;
	time_str += tmp_str;
	time_str += L' ';

}

#endif