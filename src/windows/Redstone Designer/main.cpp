#include "window.hpp"
#include "debug.hpp"
#include <comdef.h>

INT WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,INT nCmdShow)
{
	ApplicationInstance = hInstance;
	RegisterControls();
	LoadLanguageFile(CHINESE_SIMPLIFIED);
	if (!CheckTime())
	{
		MessageBox(NULL, InvalidEvaluationCopyText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		return 101;
	}
	if (InitializationCuda() != INIT_SUCCESSFULLY)
		CudaSpeedupEnabled = false;
	else
		CudaSpeedupEnabled = true;
	try
	{
		InitMainWindow(hInstance);
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UserSpecifiedApplicationExit = true;
		DeleteObject(ControlFont);
		exit(0);
	}
	//bad_alloc exception
	catch (bad_alloc)
	{
		MessageBox(NULL, OutOfMemoryErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(1);
	}
	//logic_error exception
	catch (logic_error)
	{
		MessageBox(NULL, LogicErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(2);
	}
	//COM exception
	catch (_com_error)
	{
		MessageBox(NULL, ComErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(200);
	}
	//Overflow exception
	catch (overflow_error)
	{
		MessageBox(NULL, OverflowErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(3);
	}
	//Underflow exception
	catch (underflow_error)
	{
		MessageBox(NULL, UnderflowErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(4);
	}
	catch (InvalidLanguage)
	{
		MessageBox(NULL, L"Invalid language config!\nIf you confirm this is a bug, please contact the developer.", L"Error", MB_OK | MB_ICONERROR);
		exit(5);
	}
	catch (...)
	{
		MessageBox(NULL, L"A unknown error occurred!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		exit(100);
	}
}