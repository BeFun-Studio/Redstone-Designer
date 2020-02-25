#include "main_window.hpp"

INT WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,INT nCmdShow)
{
	if (!CheckTime())
	{
		MessageBox(NULL, L"This evaluation copy of Redstone Designer has\nexpired or it is a invalid evaluation copy!", L"Error!", MB_OK | MB_ICONERROR);
		return 101;
	}
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
		DestroyMainWindow(hInstance);
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