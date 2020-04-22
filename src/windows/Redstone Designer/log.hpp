#ifndef LOG_HPP
#define LOG_HPP
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <sstream>
using namespace std;

FILE* DebugFilePointer;
bool DebugLogEnabled = false;

bool InitLog()
{
	DebugFilePointer = fopen("rsdesigner.log", "w");
	if (DebugFilePointer == NULL)
		return false;
	DebugLogEnabled = true;
	return true;
}

bool WriteLog(LPCWSTR message)
{
	if (!DebugLogEnabled)
		return false;
	SYSTEMTIME t;
	GetLocalTime(&t);
	wstring write_str = L"[";
	wstring tmp_str;
	wstringstream* converter = new wstringstream;
	*converter << t.wYear;
	*converter >> tmp_str;
	delete converter;
	write_str += tmp_str;
	write_str += L'/';
	converter = new wstringstream;
	*converter << t.wMonth;
	*converter >> tmp_str;
	delete converter;
	write_str += tmp_str;
 	write_str += L'/';
	converter = new wstringstream;
	*converter << t.wDay;
	*converter >> tmp_str;
	delete converter;
	write_str += tmp_str;
	write_str += L' ';
	converter = new wstringstream;
	*converter << t.wHour;
	*converter >> tmp_str;
	delete converter;
	if (t.wHour < 10)
		tmp_str = L"0" + tmp_str;
	write_str += tmp_str;
	write_str += L':';
	converter = new wstringstream;
	*converter << t.wMinute;
	*converter >> tmp_str;
	delete converter;
	if (t.wMinute < 10)
		tmp_str = L"0" + tmp_str;
	write_str += tmp_str;
	write_str += L':';
	converter = new wstringstream;
	*converter << t.wSecond;
	*converter >> tmp_str;
	delete converter;
	if (t.wSecond < 10)
		tmp_str = L"0" + tmp_str;
	write_str += tmp_str;
	write_str += L']';
	write_str += message;
	if (fwprintf(DebugFilePointer, L"%ls\n", write_str.c_str()) < 0)
		return false;
	return true;
}

bool WriteLog(unsigned short arg_count, ...)
{
	va_list arglist;
	arg_count *= 2;
	va_start(arglist, arg_count);
	return true;
}

#endif