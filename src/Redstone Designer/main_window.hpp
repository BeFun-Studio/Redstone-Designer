#pragma once
#include <Windows.h>
#include <vector>
#include "api.hpp"
#include "circuit.hpp"
#include "resource.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WM_SWITCH_STATUS 10000

#define MENU_BUTTON_CREATE_NEW_FILE_INDEX 1000
#define MENU_BUTTON_OPEN_EXISTING_FILE_INDEX 1001

/* These vector classes storage components' handle */
vector<HWND>buttons;
vector<HWND>edits;

enum MAIN_WINDOW_STATUS
{
	INDEX=0,
	FILE_EDITOR
};

MAIN_WINDOW_STATUS CurrentMainWindowStatus;

WNDCLASS MainWindowClass;
bool RequestedRepaintWindow;
HWND MainWindowHandle;

LRESULT MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case MENU_BUTTON_CREATE_NEW_FILE_INDEX:
		{
			OPENFILENAME open_filename = { 0 };
			wchar_t filename[16384];
			open_filename.lStructSize = sizeof(open_filename);
			open_filename.hwndOwner = hwnd;
			open_filename.lpstrFilter = L"Redstone Designer Circuit Files (*.rsd)\0*.rsd\0All Files (*.*)\0*.*\0\0";
			open_filename.lpstrFile = NULL;
			open_filename.nMaxFile = 16384;
			open_filename.lpstrDefExt = L"rsd";
			open_filename.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			GetSaveFileNameW(&open_filename);
			break;
		}
		case MENU_BUTTON_OPEN_EXISTING_FILE_INDEX:
		{
			OPENFILENAME open_filename = { 0 };
			wchar_t filename[16384];
			open_filename.lStructSize = sizeof(open_filename);
			open_filename.hwndOwner = hwnd;
			open_filename.lpstrFilter = L"Redstone Designer Circuit Files (*.rsd)\0*.rsd\0All Files (*.*)\0*.*\0\0";
			open_filename.lpstrFile = NULL;
			open_filename.nMaxFile = 16384;
			open_filename.lpstrDefExt = L"rsd";
			open_filename.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			GetOpenFileNameW(&open_filename);
		}
		}
		break;
	case WM_SWITCH_STATUS:
		for (int i = 0; i < buttons.size(); i++)
			DestroyWindow(buttons[i]);
		for (int i = 0; i < buttons.size(); i++)
			buttons.pop_back();
		switch ((unsigned char)wParam)
		{
		case INDEX:
			buttons.push_back(CreateWindow(L"BUTTON", L"❖ Create a New File", WS_CHILD | WS_VISIBLE, 5, 80, 280, 50, hwnd, (HMENU)MENU_BUTTON_CREATE_NEW_FILE_INDEX, (HINSTANCE)wParam, NULL));
			buttons.push_back(CreateWindow(L"BUTTON", L"📂 Open Existing File", WS_CHILD | WS_VISIBLE, 5, 140, 280, 50, hwnd, (HMENU)MENU_BUTTON_OPEN_EXISTING_FILE_INDEX, (HINSTANCE)wParam, NULL));
			for (int i = 0; i < buttons.size(); i++)
			{
				ShowWindow(buttons[i], SW_SHOW);
				SendMessage(buttons[i], WM_SETFONT, (WPARAM)_CreateFont(20, L"Unifont", false, false, false), NULL);
			}
			break;
		case FILE_EDITOR:
			break;
		}
	case WM_PAINT:
		/* Prepares for paint process. */
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		PAINTSTRUCT ps;
		HDC hdc;
		if (RequestedRepaintWindow)
		{
			hdc = GetDC(hwnd);
			RequestedRepaintWindow = false;
		}
		else
			hdc = BeginPaint(hwnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		FillRect(hdc, &client_rect, CreateSolidBrush(RGB(100, 100, 100)));
		switch (CurrentMainWindowStatus)
		{
		case INDEX:
			SetTextColor(hdc, RGB(255, 255, 255));
			ShadowOut(hdc, 5, 5, 30, L"Unifont", L"Redstone Designer", false, false, false);
			ShadowOut(hdc, 5, 50, 25, L"Unifont", L"➟ Select a option to continue:", false, false, false);
			break;
		}
		GetClientRect(hwnd, &client_rect);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void InitMainWindow(HINSTANCE hInstance)
{
	/* Register window class. */
	MainWindowClass = { 0 };
	MainWindowClass.lpszClassName = L"REDSTONE_DESIGNER";
	MainWindowClass.lpfnWndProc = MainWindowProc;
	MainWindowClass.hInstance = hInstance;
	MainWindowClass.hIcon = LoadIcon(hInstance, (LPCWSTR)IDI_LOGO);
	MainWindowClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	MainWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	if (RegisterClass(&MainWindowClass) == NULL)
	{
		MessageBox(NULL, L"Register Window Class Failed!", L"Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	MainWindowHandle = CreateWindow(L"REDSTONE_DESIGNER", L"Minecraft Redstone Designer", WS_OVERLAPPEDWINDOW&~WS_SIZEBOX&~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, hInstance, NULL);
	ShowWindow(MainWindowHandle, SW_SHOW);
	SendMessage(MainWindowHandle, WM_SWITCH_STATUS, (WPARAM)hInstance, NULL);
}
void DestroyMainWindow(HINSTANCE hInstance)
{
	UnregisterClass(L"REDSTONE_DESIGNER", hInstance);
}