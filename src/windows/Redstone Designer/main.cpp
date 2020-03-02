#include "window.hpp"

DWORD WINAPI BeepThreadProc(LPVOID lpParameter)
{
	Beep(530, 300);
	return 0;
}
HANDLE BeepThread;

INT WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,INT nCmdShow)
{
	if (!CheckTime())
	{
		BeepThread = CreateThread(NULL, 0, BeepThreadProc, NULL, NULL, NULL);
		MessageBox(NULL, L"This evaluation copy of Redstone Designer has\n"
			"expired or it is a invalid evaluation copy!", L"Error!", MB_OK | MB_ICONERROR);
		return 101;
	}
	if (InitializationCuda() != INIT_SUCCESSFULLY)
		CudaBoostEnabled = false;
	else
		CudaBoostEnabled = true;
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
		ApplicationDestructor(hInstance);
		return 0;
	}
	catch (bad_alloc)
	{
		MessageBox(NULL, L"No enough memory to keep the application running properly!\n\nApplication will close now.", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}
	catch (logic_error)
	{
		MessageBox(NULL, L"A serious logic error occurred.\n\nApplication will close now.", L"Error", MB_OK | MB_ICONERROR);
		return 2;
	}
	catch (...)
	{
		MessageBox(NULL, L"A unknown error occurred!\n\nApplication will close now.", L"Error", MB_OK | MB_ICONERROR);
		return 100;
	}
}