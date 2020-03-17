#include "window.hpp"
#include <comdef.h>

INT WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,INT nCmdShow)
{
	if (!CheckTime())
	{
		MessageBox(NULL, L"This evaluation copy of Redstone Designer has\n"
			"expired or it is a invalid evaluation copy!", L"Error!", MB_OK | MB_ICONERROR);
		return 101;
	}
	if (InitializationCuda() != INIT_SUCCESSFULLY)
		CudaSpeedupEnabled = false;
	else
		CudaSpeedupEnabled = true;
	try
	{
		ApplicationInstance = hInstance;
		InitMainWindow(hInstance);
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UserSpecifiedApplicationExit = true;
		WaitForSingleObject(SwitchCursorThread, INFINITE);
		DeleteObject(ControlFont);
		return 0;
	}
	//bad_alloc exception
	catch (bad_alloc)
	{
		MessageBox(NULL, L"No enough memory to keep the application running properly!\n\nApplication will  be terminated.", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}
	//logic_error exception
	catch (logic_error)
	{
		MessageBox(NULL, L"A serious logic error occurred.\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		return 2;
	}
	//COM exception
	catch (_com_error)
	{
		MessageBox(NULL, L"A serious COM error occurred.\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		return 200;
	}
	//Overflow exception
	catch (overflow_error)
	{
		MessageBox(NULL, L"A integer variable has overflowed.\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		return 3;
	}
	//Underflow exception
	catch (underflow_error)
	{
		MessageBox(NULL, L"A integer variable has underflowed.\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		return 4;
	}
	catch (...)
	{
		MessageBox(NULL, L"A unknown error occurred!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		return 100;
	}
}