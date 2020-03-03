#pragma once
#include <Windows.h>
#include <direct.h>
#include <d2d1.h>
#include <dxgi1_6.h>
#include <dwrite.h>
#include <vector>
#include <cuda_extension.cuh>
#include <ui_extension.h>
#include "api.hpp"
#include "circuit.hpp"
#include "time_checker.hpp"
#include "update.hpp"
#include "asmfuncs.h"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WM_SWITCH_STATUS 10000
#define WM_SET_DESCRIPTION_BAR 10001

#define MENU_BUTTON_CREATE_NEW_FILE_INDEX 1000
#define MENU_BUTTON_OPEN_EXISTING_FILE_INDEX 1001
#define MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_INDEX 1002
#define MENU_BUTTON_ABOUT_WINDOW_OK 1100

enum MAIN_WINDOW_STATUS
{
	INDEX=0,
	FILE_EDITOR
};

enum SelectedAction
{
	NOT_SELECTED=0,
	PLACE_REDSTONE_WIRE,
	PLACE_REDSTONE_BLOCK,
	PLACE_REDSTONE_TORCH,
	PLACE_COMMAND_BLOCK,
	PLACE_TRAP_DOOR,
	PLACE_BLOCK,
	SELECT_ITEMS,
	UNSELECT_ITEMS,

};

MAIN_WINDOW_STATUS CurrentMainWindowStatus = INDEX;
WNDCLASS MainWindowClass;
HWND MainWindowHandle;
unsigned char BlockViewSize;
CircuitLayer *CurrentLayer;
Location CurrentViewingLocation;
wstring CurrentEditingFileName;
vector<HWND>buttons;
vector<HWND>edits;
vector<HWND>editors;
wstring MainWindowDescriptionBarText;

HINSTANCE ApplicationInstance;

HANDLE UpdateMainWindowTitleThread;
HANDLE ShowUpdateAvailableTitleThread;
HANDLE CheckUpdateAvailableFlagThread;
HANDLE PlaySwitchStatusFromIndexToFileEditorAnimationThread;
HANDLE PlayPleaseWaitAnimationThread;

HFONT ShowPleaseWaitAnimationFont;

bool CudaBoostEnabled = false;
bool OpenCLBoostEnabled = false;

struct DrawingThreadParameters
{
	ID2D1RenderTarget *render_target;
};

struct DrawBlockThreadParameters :public DrawingThreadParameters
{
	ID2D1Brush* block_brush;
	ID2D1Brush* block_border_brush;
};

DWORD WINAPI UpdateMainWindowTitleThreadProc(LPVOID lPparameter)
{
	while (true)
	{
		SetWindowText(MainWindowHandle, L"Minecraft Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L" Minecraft Redstone Designe");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"  Minecraft Redstone Design");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"    Minecraft Redstone Desi");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"     Minecraft Redstone Des");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"      Minecraft Redstone De");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"       Minecraft Redstone D");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"        Minecraft Redstone ");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"         Minecraft Redstone");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"          Minecraft Redston");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"r          Minecraft Redsto");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"er          Minecraft Redst");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"ner          Minecraft Reds");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"gner          Minecraft Red");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"igner          Minecraft Re");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"signer          Minecraft R");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"esigner          Minecraft ");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"Designer          Minecraft");
		Sleep(200);
		SetWindowText(MainWindowHandle, L" Designer          Minecraf");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"e Designer          Minecra");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"ne Designer          Minecr");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"one Designer          Minec");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"tone Designer          Mine");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"stone Designer          Min");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"dstone Designer          Mi");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"edstone Designer          M");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L" Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"t Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"ft Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"aft Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"raft Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"craft Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"ecraft Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"necraft Redstone Designer");
		Sleep(200);
		SetWindowText(MainWindowHandle, L"inecraft Redstone Designer");
		Sleep(200);
	}
	return 0;
}

DWORD WINAPI ShowUpdateAvailableTitleThreadProc(LPVOID lpParameter)
{
	while(true)
	{
		SetWindowText(MainWindowHandle, L"Minecraft Redstone Designer [Update Available]");
		Sleep(1000);
		SetWindowText(MainWindowHandle, L"Minecraft Redstone Designer");
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI CheckUpdateAvailableFlagThreadProc(LPVOID lpParameter)
{
	if (IsUpdateAvailable())
	{
		ShowUpdateAvailableTitleThread = CreateThread(NULL, 0, ShowUpdateAvailableTitleThreadProc, NULL, NULL, NULL);
		TerminateThread(UpdateMainWindowTitleThread, 0);
	}
	return 0;
}

DWORD WINAPI PlaySwitchStatusFromIndexToFileEditorAnimation(LPVOID lpParameter)
{
	RECT client_rect;
	GetClientRect(MainWindowHandle, &client_rect);
	HDC hdc = GetDC(MainWindowHandle);
	unsigned char original_r = 178;
	unsigned char original_g = 34;
	unsigned char original_b = 34;
	unsigned char target_r = 211;
	unsigned char target_g = 211;
	unsigned char target_b = 211;
	for (; original_r < target_r; original_r++, original_g++, original_b++)
	{
		FillRect(hdc, &client_rect, CreateSolidBrush(RGB(original_r, original_g, original_b)));
		Sleep(4);
	}
	for (; original_g < target_g; original_g++, original_b++)
	{
		FillRect(hdc, &client_rect, CreateSolidBrush(RGB(original_r, original_g, original_b)));
		Sleep(4);
	}
	for (client_rect.top = client_rect.bottom - 1; client_rect.top > client_rect.bottom - 20; client_rect.top--)
	{
		FillRect(hdc, &client_rect, CreateSolidBrush(RGB(128, 128, 128)));
		Sleep(20);
	}
	ReleaseDC(MainWindowHandle, hdc);
	PlaySwitchStatusFromIndexToFileEditorAnimationThread = NULL;
	SendMessageW(MainWindowHandle, WM_SET_DESCRIPTION_BAR, (WPARAM)L"No item selected.", NULL);
	return 0;
}

DWORD WINAPI DrawBlocks(LPVOID lpParameter)
{
	DrawBlockThreadParameters* parameters = (DrawBlockThreadParameters*)lpParameter;
	RECT client_rect;
	GetClientRect(MainWindowHandle, &client_rect);
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
		parameters->render_target->FillRectangle(D2D1::Rect(start_draw_location.x, start_draw_location.y - BlockViewSize, start_draw_location.x + BlockViewSize, start_draw_location.y), parameters->block_border_brush);
		parameters->render_target->FillRectangle(D2D1::Rect(start_draw_location.x + 1, start_draw_location.y - BlockViewSize + 1, start_draw_location.x + BlockViewSize - 1, start_draw_location.y - 1), parameters->block_border_brush);
	}
	return 0;
}

DWORD WINAPI DrawRedstoneBlocks(LPVOID lpParameter)
{
	DrawBlockThreadParameters* parameters = (DrawBlockThreadParameters*)lpParameter;
	RECT client_rect;
	GetClientRect(MainWindowHandle, &client_rect);
	for (list<RedstoneBlock>::iterator itor = CurrentLayer->redstone_blocks.begin(); itor != CurrentLayer->redstone_blocks.end(); itor++)
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
		parameters->render_target->FillRectangle(D2D1::Rect(start_draw_location.x, start_draw_location.y, start_draw_location.x + BlockViewSize, start_draw_location.y + BlockViewSize), parameters->block_brush);
		parameters->render_target->DrawRectangle(D2D1::Rect(start_draw_location.x, start_draw_location.y, start_draw_location.x + BlockViewSize, start_draw_location.y + BlockViewSize), parameters->block_border_brush);
	}
	return 0;
}

LRESULT WINAPI MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case MENU_BUTTON_CREATE_NEW_FILE_INDEX:
		{
			CurrentEditingFileName = L"Untitled.rsd";
			SendMessage(hwnd, WM_SWITCH_STATUS, FILE_EDITOR, NULL);
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
			GetOpenFileName(&open_filename);
			break;
		}
		case MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_INDEX:
			SendMessage(hwnd, WM_SWITCH_STATUS, FILE_EDITOR, NULL);
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
		case ID_NEW_PROJECT:
		{
			OPENFILENAME open_filename = { 0 };
			wchar_t filename[16384];
			open_filename.lStructSize = sizeof(open_filename);
			open_filename.hwndOwner = hwnd;
			open_filename.lpstrFilter = L"Redstone Designer Circuit Project Files (*.rsdprj)\0*.rsdprj\0All Files (*.*)\0*.*\0\0";
			open_filename.lpstrFile = NULL;
			open_filename.nMaxFile = 16384;
			open_filename.lpstrDefExt = L"rsdprj";
			open_filename.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			GetSaveFileName(&open_filename);
			break;
		}
		}
		break;
	case WM_SET_DESCRIPTION_BAR:
	{
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		MainWindowDescriptionBarText = (LPCWSTR)wParam;
		MainWindowDescriptionBarText.insert(MainWindowDescriptionBarText.begin(), L' ');
		MainWindowDescriptionBarText.insert(MainWindowDescriptionBarText.begin(), L'>');
		InvalidateRect(hwnd, &client_rect, false);
		break;
	}
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
		case FILE_EDITOR:
		{
			if (CurrentMainWindowStatus == INDEX)
				PlaySwitchStatusFromIndexToFileEditorAnimationThread = CreateThread(NULL, 0, PlaySwitchStatusFromIndexToFileEditorAnimation, NULL, NULL, NULL);
			CurrentMainWindowStatus = FILE_EDITOR;
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
	{
		/* Prepares for paint process. */
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		/* Direct2D resources.*/
		DirectXResource<ID2D1Factory*> factory;
		DirectXResource<ID2D1HwndRenderTarget*> render_target;
		DirectXResource<ID2D1SolidColorBrush*> background_brush;
		DirectXResource<ID2D1SolidColorBrush*> text_brush;
		DirectXResource<ID2D1SolidColorBrush*> block_border_brush;
		DirectXResource<ID2D1SolidColorBrush*> circuit_bottom_brush;
		DirectXResource<IDWriteFactory*> write_factory;
		DirectXResource<IDWriteTextFormat*> title_text_format;
		DirectXResource<IDWriteTextFormat*> normal_text_format;
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factory.GetResourcePointer())))
		{
			MessageBox(hwnd, L"Create DirectX factory failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(write_factory.GetResource()), (IUnknown**)write_factory.GetResourcePointer())))
		{
			MessageBox(hwnd, L"Create DirectX write factory failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(write_factory.GetResource()->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"", title_text_format.GetResourcePointer())))
		{
			MessageBox(hwnd, L"Create DirectX text format failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(write_factory.GetResource()->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"", normal_text_format.GetResourcePointer())))
		{
			MessageBox(hwnd, L"Create DirectX text format failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(factory.GetResource()->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(client_rect.right, client_rect.bottom)), render_target.GetResourcePointer())))
		{
			MessageBox(hwnd, L"Create DirectX render target failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		title_text_format.GetResource()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		title_text_format.GetResource()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		normal_text_format.GetResource()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		normal_text_format.GetResource()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		if (CurrentMainWindowStatus == INDEX)
		{
			if (FAILED(render_target.GetResource()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Firebrick), background_brush.GetResourcePointer())))
			{
				MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
		}
		else
		{
			if (FAILED(render_target.GetResource()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), background_brush.GetResourcePointer())))
			{
				MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
		}
		if (FAILED(render_target.GetResource()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), text_brush.GetResourcePointer())))
		{
			MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(render_target.GetResource()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), block_border_brush.GetResourcePointer())))
		{
			MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(render_target.GetResource()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGray), circuit_bottom_brush.GetResourcePointer())))
		{
			MessageBox(hwnd, L"Create DirectX brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		render_target.GetResource()->BeginDraw();
		render_target.GetResource()->Clear(D2D1::ColorF(D2D1::ColorF::White));
		render_target.GetResource()->FillRectangle(D2D1::Rect(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), background_brush.GetResource());
		switch (CurrentMainWindowStatus)
		{
		case INDEX:
			render_target.GetResource()->DrawText(L"Redstone Designer", wcslen(L"Redstone Designer"), title_text_format.GetResource(), &D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.GetResource(), D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
			render_target.GetResource()->DrawText(L"\n\nChoose a option to continue:", wcslen(L"\n\nChoose a option to continue:"), normal_text_format.GetResource(), &D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.GetResource(), D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
			break;
		case FILE_EDITOR:
		{
			if (CurrentEditingFileName.length() == 0)
				break;
			render_target.GetResource()->FillRectangle(D2D1::Rect(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), circuit_bottom_brush.GetResource());
			render_target.GetResource()->DrawText(L"File:", wcslen(L"File"), normal_text_format.GetResource(), &D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.GetResource(), D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
			render_target.GetResource()->DrawText((L"File:" + CurrentEditingFileName).c_str(), wcslen(L"File:") + CurrentEditingFileName.length(), normal_text_format.GetResource(), &D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.GetResource(), D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
			DrawBlockThreadParameters draw_block_thread_parameters;
			draw_block_thread_parameters.block_border_brush = block_border_brush.GetResource();
			draw_block_thread_parameters.block_brush = text_brush.GetResource();
			draw_block_thread_parameters.render_target = render_target.GetResource();
			HANDLE DrawBlockThread = CreateThread(NULL, NULL, DrawBlocks, &draw_block_thread_parameters, NULL, NULL);
			break;
		}
		}
		if (CurrentMainWindowStatus != INDEX && PlaySwitchStatusFromIndexToFileEditorAnimationThread == NULL)
			render_target.GetResource()->FillRectangle(D2D1::Rect(client_rect.left, client_rect.bottom - 20, client_rect.right, client_rect.bottom), block_border_brush.GetResource());
		if (FAILED(render_target.GetResource()->EndDraw()))
			if (MessageBox(hwnd, L"Draw failed!\n\nContinue?", L"Error", MB_YESNO | MB_ICONWARNING) == IDNO)
			{
				PostQuitMessage(1);
			}
		if (CurrentMainWindowStatus != INDEX && PlaySwitchStatusFromIndexToFileEditorAnimationThread == NULL)
		{
			HDC hdc = GetDC(hwnd);
			HFONT font = _CreateFont(18, L"Unifont", false, false, false);
			SelectObject(hdc, font);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, client_rect.left, client_rect.bottom - 20, MainWindowDescriptionBarText.c_str(), wcslen(MainWindowDescriptionBarText.c_str()));
			DeleteObject(font);
		}
		title_text_format.Release();
		write_factory.Release();
		render_target.Release();
		block_border_brush.Release();
		circuit_bottom_brush.Release();
		text_brush.Release();
		background_brush.Release();
		factory.Release();
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	#ifdef ENABLE_TIME_CHECK
	if (PlaySwitchStatusFromIndexToFileEditorAnimationThread == NULL)
	{
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		HDC hdc = GetDC(hwnd);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));
		if (CurrentMainWindowStatus == INDEX)
		{
			TextOut(hdc, 0, client_rect.bottom - 31, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 16, L"For testing purposes only. Inside Test 0", wcslen(L"For testing purposes only. Inside Test 0"));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, 0, client_rect.bottom - 33, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 18, L"For testing purposes only. Inside Test 0", wcslen(L"For testing purposes only. Inside Test 0"));
		}
		else
		{
			TextOut(hdc, 0, client_rect.bottom - 51, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 36, L"For testing purposes only. Inside Test 0", wcslen(L"For testing purposes only. Inside Test 0"));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, 0, client_rect.bottom - 53, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 38, L"For testing purposes only. Inside Test 0", wcslen(L"For testing purposes only. Inside Test 0"));
		}
		ReleaseDC(hwnd, hdc);
	}
	#endif
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
	MainWindowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	if (RegisterClass(&MainWindowClass) == NULL)
	{
		MessageBox(NULL, L"Register Window Class Failed!", L"Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	MainWindowHandle = CreateWindow(L"REDSTONE_DESIGNER", L"Minecraft Redstone Designer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, hInstance, NULL);
	ShowWindow(MainWindowHandle, SW_SHOW);
	SendMessage(MainWindowHandle, WM_SWITCH_STATUS, (WPARAM)hInstance, NULL);
	UpdateMainWindowTitleThread = CreateThread(NULL, 0, UpdateMainWindowTitleThreadProc, NULL, NULL, NULL);
	CheckUpdateAvailableFlagThread = CreateThread(NULL, 0, CheckUpdateAvailableFlagThreadProc, NULL, NULL, NULL);
}
void ApplicationDestructor(HINSTANCE hInstance)
{
	UnregisterClass(L"REDSTONE_DESIGNER", hInstance);
}