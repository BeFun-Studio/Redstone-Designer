#pragma once
#include <Windows.h>

#define ENABLE_TIME_CHECK

#define EVALUATION_START_YEAR 2020
#define EVALUATION_START_MONTH 4
#define EVALUATION_START_DAY 21

#define EXPIRATION_YEAR 2020
#define EXPIRATION_MONTH 5
#define EXPIRATION_DAY 14

bool CheckTime()
{
	#ifdef ENABLE_TIME_CHECK
	SYSTEMTIME system_time_checker = { 0 };
	GetSystemTime(&system_time_checker);
	if (system_time_checker.wYear < EVALUATION_START_YEAR)
		return false;
	if (system_time_checker.wMonth < EVALUATION_START_MONTH && system_time_checker.wYear == EVALUATION_START_YEAR)
		return false;
	if (system_time_checker.wDay < EVALUATION_START_DAY && system_time_checker.wMonth == EVALUATION_START_MONTH && system_time_checker.wYear == EVALUATION_START_YEAR)
		return false;
	if (system_time_checker.wYear > EXPIRATION_YEAR)
		return false;
	else if (system_time_checker.wMonth > EXPIRATION_MONTH&& system_time_checker.wYear == EXPIRATION_YEAR)
		return false;
	else if (system_time_checker.wDay > EXPIRATION_DAY&& system_time_checker.wMonth == EXPIRATION_MONTH&& system_time_checker.wYear == EXPIRATION_YEAR)
		return false;
	#endif
	return true;
}