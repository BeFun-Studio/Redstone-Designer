#pragma once
#include <Windows.h>
#include <direct.h>
#include <d2d1.h>
#include <d3d12.h>
#include <dwrite.h>
#include <vector>
#include "api.hpp"
#include "circuit.hpp"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WM_SWITCH_STATUS 10000

#define MENU_BUTTON_CREATE_NEW_FILE_INDEX 1000
#define MENU_BUTTON_OPEN_EXISTING_FILE_INDEX 1001
#define MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_INDEX 1002

enum MAIN_WINDOW_STATUS
{
	INDEX=0,
	FILE_EDITORS
};

MAIN_WINDOW_STATUS CurrentMainWindowStatus;
WNDCLASS MainWindowClass;
bool RequestedRepaintWindow;
HWND MainWindowHandle;
unsigned char BlockViewSize;
CircuitLayer *CurrentLayer;
Location CurrentViewingLocation;
wstring CurrentEditingFileName;
vector<HWND>buttons;
vector<HWND>edits;
vector<HWND>editors;
HINSTANCE ApplicationInstance;

LRESULT MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case MENU_BUTTON_CREATE_NEW_FILE_INDEX:
		{
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
			break;
		}
		case MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_INDEX:
			SendMessage(hwnd, WM_SWITCH_STATUS, FILE_EDITORS, NULL);
			RECT client_rect;
			GetClientRect(hwnd, &client_rect);
			InvalidateRect(hwnd, &client_rect, false);
			break;
		case ID_NEW_CIRCUITFILE:
			SendMessage(hwnd, WM_COMMAND, MENU_BUTTON_CREATE_NEW_FILE_INDEX, NULL);
			break;
		case ID_FILE_OPEN:
			SendMessage(hwnd, WM_COMMAND, MENU_BUTTON_OPEN_EXISTING_FILE_INDEX, NULL);
			break;
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
		{
			buttons.push_back(CreateWindow(L"BUTTON", L"Create a New File >", WS_CHILD | WS_VISIBLE, 5, 80, 360, 50, hwnd, (HMENU)MENU_BUTTON_CREATE_NEW_FILE_INDEX, (HINSTANCE)wParam, NULL));
			buttons.push_back(CreateWindow(L"BUTTON", L"Open Existing File >", WS_CHILD | WS_VISIBLE, 5, 140, 360, 50, hwnd, (HMENU)MENU_BUTTON_OPEN_EXISTING_FILE_INDEX, (HINSTANCE)wParam, NULL));
			buttons.push_back(CreateWindow(L"BUTTON", L"Continue Without Any Operation >", WS_CHILD | WS_VISIBLE, 5, 200, 360, 50, hwnd, (HMENU)MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_INDEX, (HINSTANCE)wParam, NULL));
			for (int i = 0; i < buttons.size(); i++)
			{
				ShowWindow(buttons[i], SW_SHOW);
				SendMessage(buttons[i], WM_SETFONT, (WPARAM)_CreateFont(20, L"Unifont", false, false, false), NULL);
			}
			CurrentMainWindowStatus = INDEX;
			break;
		}
		case FILE_EDITORS:
		{
			RECT client_rect;
			GetClientRect(hwnd, &client_rect);
			HDC hdc = GetDC(hwnd);
			unsigned char original_r = 178;
			unsigned char original_g = 34;
			unsigned char original_b = 34;
			unsigned char target_r = 211;
			unsigned char target_g = 211;
			unsigned char target_b = 211;
			for (; original_r < target_r; original_r++, original_g++, original_b++)
			{
				FillRect(hdc, &client_rect, CreateSolidBrush(RGB(original_r, original_g, original_b)));
				Sleep(1);
			}
			for (; original_g < target_g; original_g++, original_b++)
			{
				FillRect(hdc, &client_rect, CreateSolidBrush(RGB(original_r, original_g, original_b)));
				Sleep(1);
			}
			CurrentMainWindowStatus = FILE_EDITORS;
			break;
		}
		}
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(hwnd, L"Are you sure want to exit?\nAll changes will not be saved!", L"Exit?", MB_YESNO | MB_ICONWARNING) == IDYES)
				PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		/* Prepares for paint process. */
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		ID2D1Factory* factory;
		ID2D1HwndRenderTarget* render_target;
		ID2D1SolidColorBrush* background_brush;
		ID2D1SolidColorBrush* text_brush;
		ID2D1SolidColorBrush* block_border_brush;
		IDWriteFactory* write_factory;
		IDWriteTextFormat* title_text_format;
		IDWriteTextFormat* normal_text_format;
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory)))
		{
			MessageBox(hwnd, L"Create DirectX factory failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(write_factory), (IUnknown**)&write_factory)))
		{
			MessageBox(hwnd, L"Create DirectX write factory failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(write_factory->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"", &title_text_format)))
		{
			MessageBox(hwnd, L"Create DirectX text format failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(write_factory->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"", &normal_text_format)))
		{
			MessageBox(hwnd, L"Create DirectX text format failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(client_rect.right, client_rect.bottom)), &render_target)))
		{
			MessageBox(hwnd, L"Create DirectX render target failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		title_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		title_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		normal_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		normal_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		if (CurrentMainWindowStatus == INDEX)
		{
			if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Firebrick), &background_brush)))
			{
				MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
		}
		else
		{
			if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), &background_brush)))
			{
				MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
		}
		if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &text_brush)))
		{
			MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &block_border_brush)))
		{
			MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		render_target->BeginDraw();
		render_target->Clear(D2D1::ColorF(D2D1::ColorF::White));
		render_target->FillRectangle(D2D1::Rect(client_rect.left,client_rect.top,client_rect.right,client_rect.bottom), background_brush);
		switch (CurrentMainWindowStatus)
		{
		case INDEX:
			render_target->DrawText(L"Redstone Designer", wcslen(L"Redstone Designer"), title_text_format, &D2D1::RectF(client_rect.left,client_rect.top,client_rect.right,client_rect.bottom), text_brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
			render_target->DrawText(L"\n\nChoose a option to continue:", wcslen(L"\n\nChoose a option to continue:"), normal_text_format, &D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
			break;
		case FILE_EDITORS:
			if (CurrentEditingFileName.empty())
				break;
			for (int i = 0; i < client_rect.right; i++)
				for (int j = 0; j < client_rect.bottom; j++)
				{
					for (list<Block>::iterator itor = CurrentLayer->blocks.begin(); itor != CurrentLayer->blocks.end(); itor++)
					{
						Location start_draw_location;
						const int block_count_can_display_x = client_rect.right / BlockViewSize;
						const int block_count_can_display_y = client_rect.bottom / BlockViewSize;
						if (abs(itor->GetLocation().x - CurrentViewingLocation.x) <= block_count_can_display_x)
							if (itor->GetLocation().x - CurrentViewingLocation.x < 0)
								start_draw_location.x = block_count_can_display_x * BlockViewSize / 2 - BlockViewSize * abs(itor->GetLocation().x - CurrentViewingLocation.x);
						if (abs(itor->GetLocation().y - CurrentViewingLocation.y) <= block_count_can_display_y)
							if (itor->GetLocation().y - CurrentViewingLocation.y < 0)
								start_draw_location.y = block_count_can_display_y * BlockViewSize / 2 - BlockViewSize * abs(itor->GetLocation().y - CurrentViewingLocation.y);
						render_target->FillRectangle(D2D1::Rect(start_draw_location.x, start_draw_location.y, start_draw_location.x + BlockViewSize, start_draw_location.y + BlockViewSize), text_brush);
						render_target->DrawRectangle(D2D1::Rect(start_draw_location.x, start_draw_location.y, start_draw_location.x + BlockViewSize, start_draw_location.y + BlockViewSize), block_border_brush);
					}
				}
			break;
		}
		if (FAILED(render_target->EndDraw()))
			if (MessageBox(hwnd, L"Draw failed!\n\nContinue?", L"Error", MB_YESNO | MB_ICONWARNING) == IDNO)
			{
				PostQuitMessage(1);
			}
		RELEASE_D2D_RESOURCE(title_text_format);
		RELEASE_D2D_RESOURCE(write_factory);
		RELEASE_D2D_RESOURCE(render_target);
		RELEASE_D2D_RESOURCE(block_border_brush);
		RELEASE_D2D_RESOURCE(text_brush);
		RELEASE_D2D_RESOURCE(background_brush);
		RELEASE_D2D_RESOURCE(factory);
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
	MainWindowClass.lpszMenuName = (LPCWSTR)IDR_MENU;
	if (RegisterClass(&MainWindowClass) == NULL)
	{
		MessageBox(NULL, L"Register Window Class Failed!", L"Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	MainWindowHandle = CreateWindow(L"REDSTONE_DESIGNER", L"Minecraft Redstone Designer", WS_OVERLAPPEDWINDOW&~WS_SIZEBOX&~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, hInstance, NULL);
	ShowWindow(MainWindowHandle, SW_SHOW);
	SendMessage(MainWindowHandle, WM_SWITCH_STATUS, (WPARAM)hInstance, NULL);
}
DWORD RequestedRepaintMainWindowFlagCheckThread(LPVOID lpParameter)
{
	while (true)
	{
		if (RequestedRepaintWindow)
		{
			SendMessage(MainWindowHandle, WM_PAINT, NULL, NULL);
			RequestedRepaintWindow = false;
		}
		Sleep(1);
	}
}
void DestroyMainWindow(HINSTANCE hInstance)
{
	UnregisterClass(L"REDSTONE_DESIGNER", hInstance);
}