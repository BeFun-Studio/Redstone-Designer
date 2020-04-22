#include "window.hpp"
#include <comdef.h>

INT WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,INT nCmdShow)
{
	InitLog();
	WriteLog(L"Launched Redstone Designer.");
	ApplicationInstance = hInstance;
	WriteLog(L"Registering controls...");
	try
	{
		RegisterControls();
		WriteLog(L"Register controls successfully.");
		WriteLog(L"Loading language files...");
		LoadLanguageFile(CHINESE_SIMPLIFIED);
		WriteLog(L"Load language files successfully.");
		if (!CheckTime())
		{
			WriteLog(L"This evaluation copy is invalid!Application will be terminated.");
			MessageBox(NULL, InvalidEvaluationCopyText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			return 101;
		}
		WriteLog(L"Initializing CUDA...");
		if (InitializationCuda() != INIT_SUCCESSFULLY)
		{
			WriteLog(L"Initialization CUDA failed, the CUDA speedup will be disabled.");
			CudaSpeedupEnabled = false;
		}
		else
		{
			WriteLog(L"Initialization CUDA successfully.");
			CudaSpeedupEnabled = true;
		}
		WriteLog(L"Initializing main window...");
		InitMainWindow(hInstance);
		WriteLog(L"Initialization main window successfully.");
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		WriteLog(L"Destroyed main window.");
		WriteLog(L"Exiting threads...");
		UserSpecifiedApplicationExit = true;
		WriteLog(L"Releasing resources...");
		DeleteObject(ControlFont);
		WriteLog(L"Exited application.");
		exit(0);
	}
	//bad_alloc exception
	catch (bad_alloc)
	{
		WriteLog(L"Out of memory!Application will be terminated.");
		MessageBox(NULL, OutOfMemoryErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(1);
	}
	//logic_error exception
	catch (logic_error)
	{
		WriteLog(L"A serious logic error detected!Application will be terminated.");
		MessageBox(NULL, LogicErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(2);
	}
	//COM exception
	catch (_com_error)
	{
		WriteLog(L"A serious COM error detected!Application will be terminated.");
		MessageBox(NULL, ComErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(200);
	}
	//Overflow exception
	catch (overflow_error)
	{
		WriteLog(L"A serious overflow error detected!Application will be terminated.");
		MessageBox(NULL, OverflowErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(3);
	}
	//Underflow exception
	catch (underflow_error)
	{
		WriteLog(L"A serious underflow error detected!Application will be terminated.");
		MessageBox(NULL, UnderflowErrorText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(4);
	}
	catch (InvalidLanguage)
	{
		WriteLog(L"Invalid language config!Application will be terminated.");
		MessageBox(NULL, L"Invalid language config!\nIf you confirm this is a bug, please contact the developer.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(5);
	}
	catch (RegisterControlsFailed)
	{
		WriteLog(L"Register controls failed!Application will be terminated.");
		MessageBox(NULL, L"Register controls failed!", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(6);
	}
	catch (InitializationControlFailed)
	{
		WriteLog(L"A serious error has occurred when initialization a control.Application will be terminated.");
		MessageBox(NULL, L"Register controls failed!\nIf you confirm this is a bug, please contact the developer.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(7);
	}
	catch (...)
	{
		WriteLog(L"A unknown exception detected!Application will be terminated.");
		MessageBox(NULL, L"A unknown exception occurred!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		exit(100);
	}
}