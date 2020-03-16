#pragma once
#include <Windows.h>
#include <direct.h>
#include <d2d1_3.h>
#include <dxgi1_6.h>
#include <d3d11.h>
#include <dwrite.h>
#include <vector>
#include <wincodec.h>
#include <cuda_extension.cuh>
#include <ui_extension.h>
#include <wrl.h>
#include "api.hpp"
#include "circuit.hpp"
#include "time_checker.hpp"
#include "update.hpp"
#include "asmfuncs.h"
#include "resource.h"
using namespace Microsoft::WRL;

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
unsigned char BlockViewSize = 75;
CircuitLayer *CurrentLayer;
Position CurrentViewingPosition;
wstring CurrentEditingFileName;
vector<HWND>buttons;
vector<HWND>edits;
vector<HWND>editors;
wstring MainWindowDescriptionBarText;

struct ShowedComponent
{
	Component* component;
	RECT owned_area;
};

struct ShowedBlock
{
	Block* block;
	RECT owned_area;
};

vector<ShowedComponent>ShowedComponents;
vector<ShowedBlock>ShowedBlocks;

vector<Block*>SelectedBlocks;
vector<Component*>SelectedComponents;

HINSTANCE ApplicationInstance;

HANDLE UpdateMainWindowTitleThread;
HANDLE ShowUpdateAvailableTitleThread;
HANDLE CheckUpdateAvailableFlagThread;
HANDLE PlayPleaseWaitAnimationThread;
HANDLE SwitchCursorThread;
HANDLE AboutWindowThread;

HANDLE DrawBlocksThread;
HANDLE DrawRedstoneBlocksThread;

HFONT ShowPleaseWaitAnimationFont;
const HFONT ControlFont = _CreateFont(18, L"Unifont", false, false, false);

bool CudaBoostEnabled = false;
bool OpenCLBoostEnabled = false;

bool UserSpecifiedApplicationExit = false;

ComPtr<ID2D1Bitmap> NormalBlockTexture;
ComPtr<ID2D1Bitmap> SlabUpperTexture;
ComPtr<ID2D1Bitmap> SlabLowerTexture;
ComPtr<ID2D1Bitmap> StairEastTexture;
ComPtr<ID2D1Bitmap> StairNorthTexture;
ComPtr<ID2D1Bitmap> StairWestTexture;
ComPtr<ID2D1Bitmap> StairSouthTexture;
ComPtr<ID2D1Bitmap> StairUpperEastTexture;
ComPtr<ID2D1Bitmap> StairUpperNorthTexture;
ComPtr<ID2D1Bitmap> StairUpperWestTexture;
ComPtr<ID2D1Bitmap> StairUpperSouthTexture;
ComPtr<ID2D1Bitmap> CommandBlockTexture;
ComPtr<ID2D1Bitmap> RedstoneWireTexture;
ComPtr<ID2D1Bitmap> RedstoneBlockTexture;
ComPtr<ID2D1Bitmap> RedstoneBlockTorchEastTexture;
ComPtr<ID2D1Bitmap> RedstoneBlockTorchNorthTexture;
ComPtr<ID2D1Bitmap> RedstoneBlockTorchWestTexture;
ComPtr<ID2D1Bitmap> RedstoneBlockTorchSouthTexture;
ComPtr<ID2D1Bitmap> TrapDoorEastTexture;
ComPtr<ID2D1Bitmap> TrapDoorWestTexture;
ComPtr<ID2D1Bitmap> TrapDoorNorthTexture;
ComPtr<ID2D1Bitmap> TrapDoorSouthTexture;
ComPtr<ID2D1Bitmap> TrapDoorEastOpenedTexture;
ComPtr<ID2D1Bitmap> TrapDoorWestOpenedTexture;
ComPtr<ID2D1Bitmap> TrapDoorNorthOpenedTexture;
ComPtr<ID2D1Bitmap> TrapDoorSouthOpenedTexture;
ComPtr<ID2D1Bitmap> ChestEastTexture;
ComPtr<ID2D1Bitmap> ChestWestTexture;
ComPtr<ID2D1Bitmap> ChestNorthTexture;
ComPtr<ID2D1Bitmap> ChestSouthTexture;
ComPtr<ID2D1Bitmap> TrapChestEastTexture;
ComPtr<ID2D1Bitmap> TrapChestWestTexture;
ComPtr<ID2D1Bitmap> TrapChestNorthTexture;
ComPtr<ID2D1Bitmap> TrapChestSouthTexture;

struct DrawingThreadParameters
{
	ID2D1DeviceContext* device_context;
};

struct DrawBlockThreadParameters :public DrawingThreadParameters
{
	ID2D1Brush* block_brush;
	ID2D1Brush* block_border_brush;
};

void NewCircuitFile(LPCWSTR file_name)
{
	CircuitLayer push_layer;
	CircuitLayers.push_back(push_layer);
	CurrentLayer = &CircuitLayers.back();
	Block init_block;
	for(signed char i=-5;i<=5;i++)
		for (signed char j = -5; j <= 5; j++)
		{
			init_block.SetPosition(i, j);
			CurrentLayer->blocks.push_back(init_block);
		}
	CurrentViewingPosition = { 0,0 };
	CurrentEditingFileName = file_name;
}

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

DWORD WINAPI SwitchCursorThreadProc(LPVOID lpParameter)
{
	while (true)
	{
		if (CurrentMainWindowStatus == INDEX)
			SetCursor(LoadCursor(ApplicationInstance, (LPCWSTR)IDC_ARROW));
		else
		{
			HDC hdc = GetDC(MainWindowHandle);
			POINT cursor_point;
			GetCursorPos(&cursor_point);
			if (GetRValue(GetPixel(hdc, cursor_point.x, cursor_point.y)) > 127 && GetGValue(GetPixel(hdc, cursor_point.x, cursor_point.y)) > 127 && GetBValue(GetPixel(hdc, cursor_point.x, cursor_point.y)) > 127)
				SetCursor(LoadCursor(ApplicationInstance, (LPCWSTR)IDC_INDICATOR_DARK));
			else
				SetCursor(LoadCursor(ApplicationInstance, (LPCWSTR)IDC_INDICATOR_LIGHT));
			ReleaseDC(MainWindowHandle, hdc);
		}
		if (UserSpecifiedApplicationExit)
			break;
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

LRESULT WINAPI AboutWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, ControlFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 5, 5, L"Minecraft Redstone Designer", wcslen(L"Minecraft Redstone Designer"));
		TextOut(hdc, 5, 30, L"Copyright(C)2020 CodesBuilder", wcslen(L"Copyright(C)2020 CodesBuilder"));
		RECT draw_rect = client_rect;
		draw_rect.top = 55;
		draw_rect.bottom = 56;
		draw_rect.left += 5;
		draw_rect.right -= 5;
		FillRect(hdc, &draw_rect, CreateSolidBrush(RGB(0, 0, 0)));
		SetTextColor(hdc, RGB(100, 150, 100));
		if (CudaBoostEnabled)
			TextOut(hdc, 5, 60, L"CUDA Boost:Enabled", wcslen(L"CUDA Boost:Enabled"));
		else
			TextOut(hdc, 5, 60, L"CUDA Boost:Disabled", wcslen(L"CUDA Boost:Disabled"));
		SetTextColor(hdc, RGB(178,34,34));
		if (OpenCLBoostEnabled)
			TextOut(hdc, 5, 85, L"OpenCL Boost:Enabled", wcslen(L"OpenCL Boost:Enabled"));
		else
			TextOut(hdc, 5, 85, L"OpenCL Boost:Disabled", wcslen(L"OpenCL Boost:Disabled"));
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		UnregisterClass(L"ABOUT_REDSTONE_DESIGNER", ApplicationInstance);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void InitAboutWindow()
{
	WNDCLASS about_window_class = { 0 };
	HWND about_window_handle;
	about_window_class.hCursor = LoadCursor(ApplicationInstance, (LPCWSTR)IDC_ARROW);
	about_window_class.lpszClassName = L"ABOUT_REDSTONE_DESIGNER";
	about_window_class.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
	about_window_class.hIcon = LoadIcon(ApplicationInstance, (LPCWSTR)IDI_REDSTONE_TOOLS);
	about_window_class.lpfnWndProc = AboutWindowProc;
	if (RegisterClass(&about_window_class) == NULL)
	{
		MessageBox(MainWindowHandle, L"Register window class failed!\nApplication will be terminated", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	about_window_handle = CreateWindowEx(WS_EX_TOOLWINDOW, L"ABOUT_REDSTONE_DESIGNER", L"About Redstone Designer", WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, MainWindowHandle, NULL, ApplicationInstance, NULL);
	if (about_window_handle == NULL)
	{
		MessageBox(MainWindowHandle, L"Create window failed!\nApplication will be terminated", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	ShowWindow(about_window_handle, SW_SHOW);
}

DWORD WINAPI DrawBlocks(LPVOID lpParameter)
{
	for(int i=0;i<ShowedBlocks.size();i++)
		ShowedBlocks.pop_back();
	DrawBlockThreadParameters* parameters = (DrawBlockThreadParameters*)lpParameter;
	RECT client_rect;
	GetClientRect(MainWindowHandle, &client_rect);
	if (CurrentLayer->blocks.size() == 0)
		return 0;
	for (list<Block>::iterator itor = CurrentLayer->blocks.begin(); itor != CurrentLayer->blocks.end(); itor++)
	{
		Position start_draw_position;
		const int block_count_can_be_displayed_x = client_rect.right / BlockViewSize;
		const int block_count_can_be_displayed_y = client_rect.bottom / BlockViewSize;
		if (abs(itor->GetPosition().x - CurrentViewingPosition.x) <= block_count_can_be_displayed_x)
			if (itor->GetPosition().x - CurrentViewingPosition.x < 0)
				start_draw_position.x = client_rect.right / 2 - abs(CurrentViewingPosition.x - itor->GetPosition().x) * BlockViewSize;
			else
				start_draw_position.x = client_rect.right / 2 - abs(itor->GetPosition().x - CurrentViewingPosition.x) * BlockViewSize;
		if (abs(itor->GetPosition().y - CurrentViewingPosition.y) <= block_count_can_be_displayed_y)
			if (itor->GetPosition().y - CurrentViewingPosition.y < 0)
				start_draw_position.y = client_rect.bottom / 2 - abs(CurrentViewingPosition.y - itor->GetPosition().y) * BlockViewSize;
			else
				start_draw_position.y = client_rect.bottom / 2 - abs(itor->GetPosition().y - CurrentViewingPosition.y) * BlockViewSize;
		for (int i = 0; i < SelectedBlocks.size(); i++)
			if (&(*itor) == SelectedBlocks[i])
			{
				parameters->block_border_brush->SetOpacity(0.1);
			}
		parameters->device_context->FillRectangle(D2D1::RectF(start_draw_position.x - BlockViewSize / 2, start_draw_position.y - BlockViewSize / 2, start_draw_position.x + BlockViewSize / 2, start_draw_position.y + BlockViewSize / 2), parameters->block_border_brush);
		parameters->device_context->FillRectangle(D2D1::RectF(start_draw_position.x - BlockViewSize / 2 + 2, start_draw_position.y - BlockViewSize / 2 + 2, start_draw_position.x + BlockViewSize / 2 - 2, start_draw_position.y + BlockViewSize / 2 - 2), parameters->block_brush);
		ShowedBlock push_block;
		push_block.block = &(*itor);
		push_block.owned_area.left = start_draw_position.x - BlockViewSize / 2;
		push_block.owned_area.top = start_draw_position.y - BlockViewSize / 2;
		push_block.owned_area.right = start_draw_position.x + BlockViewSize / 2;
		push_block.owned_area.bottom = start_draw_position.y + BlockViewSize / 2;
		ShowedBlocks.push_back(push_block);
	}
	DrawBlocksThread = NULL;
	return 0;
}

DWORD WINAPI DrawRedstoneBlocks(LPVOID lpParameter)
{
	DrawBlockThreadParameters* parameters = (DrawBlockThreadParameters*)lpParameter;
	RECT client_rect;
	GetClientRect(MainWindowHandle, &client_rect);
	for (list<RedstoneBlock>::iterator itor = CurrentLayer->redstone_blocks.begin(); itor != CurrentLayer->redstone_blocks.end(); itor++)
	{
		Position start_draw_position;
		const int block_count_can_display_x = client_rect.right / BlockViewSize;
		const int block_count_can_display_y = client_rect.bottom / BlockViewSize;
		if (abs(itor->GetPosition().x - CurrentViewingPosition.x) <= block_count_can_display_x)
			if (itor->GetPosition().x - CurrentViewingPosition.x < 0)
				start_draw_position.x = block_count_can_display_x * BlockViewSize / 2 - BlockViewSize * abs(itor->GetPosition().x - CurrentViewingPosition.x);
		if (abs(itor->GetPosition().y - CurrentViewingPosition.y) <= block_count_can_display_y)
			if (itor->GetPosition().y - CurrentViewingPosition.y < 0)
				start_draw_position.y = block_count_can_display_y * BlockViewSize / 2 - BlockViewSize * abs(itor->GetPosition().y - CurrentViewingPosition.y);
		parameters->device_context->FillRectangle(D2D1::RectF(start_draw_position.x, start_draw_position.y, start_draw_position.x + BlockViewSize, start_draw_position.y + BlockViewSize), parameters->block_brush);
		parameters->device_context->DrawRectangle(D2D1::RectF(start_draw_position.x, start_draw_position.y, start_draw_position.x + BlockViewSize, start_draw_position.y + BlockViewSize), parameters->block_border_brush);
	}
	DrawRedstoneBlocksThread = NULL;
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
			NewCircuitFile(L"Untitled.rsd");
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
		case ID_FILE_SAVE:

		case ID_HELP_ABOUT:
			InitAboutWindow();
			break;
		case ID_NEW_PROJECT:
		{
			OPENFILENAME open_filename = { 0 };
			wchar_t filename[8193];
			open_filename.lStructSize = sizeof(open_filename);
			open_filename.hwndOwner = hwnd;
			open_filename.lpstrFilter = L"Redstone Designer Circuit Project Files (*.rsdprj)\0*.rsdprj\0All Files (*.*)\0*.*\0\0";
			open_filename.lpstrFile = NULL;
			open_filename.nMaxFile = 8192;
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
		buttons.clear();
		buttons.shrink_to_fit();
		for (int i = 0; i < edits.size(); i++)
			DestroyWindow(edits[i]);
		edits.clear();
		edits.shrink_to_fit();
		switch ((unsigned char)wParam)
		{
		case INDEX:
		{
			buttons.push_back(CreateWindow(L"BUTTON", L"Create a New File >", WS_CHILD | WS_VISIBLE, 10, 80, 360, 50, hwnd, (HMENU)MENU_BUTTON_CREATE_NEW_FILE_INDEX, (HINSTANCE)wParam, NULL));
			buttons.push_back(CreateWindow(L"BUTTON", L"Open Existing File >", WS_CHILD | WS_VISIBLE, 10, 140, 360, 50, hwnd, (HMENU)MENU_BUTTON_OPEN_EXISTING_FILE_INDEX, (HINSTANCE)wParam, NULL));
			buttons.push_back(CreateWindow(L"BUTTON", L"Continue Without Any Operation >", WS_CHILD | WS_VISIBLE, 10, 200, 360, 50, hwnd, (HMENU)MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_INDEX, (HINSTANCE)wParam, NULL));
			for (int i = 0; i < buttons.size(); i++)
			{
				ShowWindow(buttons[i], SW_SHOW);
				SendMessage(buttons[i], WM_SETFONT, (WPARAM)ControlFont, NULL);
			}
			CurrentMainWindowStatus = INDEX;
			break;
		}
		case FILE_EDITOR:
		{
			RECT client_rect;
			GetClientRect(hwnd, &client_rect);
			InvalidateRect(hwnd, &client_rect, false);
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
	case WM_LBUTTONDOWN:
	{
		if (CurrentMainWindowStatus != FILE_EDITOR)
			break;
		SelectedBlocks.clear();
		SelectedBlocks.shrink_to_fit();
		int mouse_x = LOWORD(lParam);
		int mouse_y = HIWORD(lParam);
		for (int i = 0; i < ShowedBlocks.size(); i++)
		{
			if (mouse_x > ShowedBlocks[i].owned_area.left&& mouse_y > ShowedBlocks[i].owned_area.top&& mouse_x < ShowedBlocks[i].owned_area.right && mouse_y < ShowedBlocks[i].owned_area.bottom)
			{
				SelectedBlocks.push_back(ShowedBlocks[i].block);
				break;
			}
		}
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		InvalidateRect(hwnd, &client_rect, false);
		break;
	}
	case WM_PAINT:
	{
		/* Prepares for paint process. */
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		/* Direct2D resources.*/
		ComPtr<ID2D1Factory1> factory;
		ComPtr<ID3D11DeviceContext> device_context;
		ComPtr<ID3D11Device> device;
		ComPtr<ID2D1Device> device_2d;
		ComPtr<ID2D1DeviceContext> device_context_2d;
		ComPtr<IDXGIDevice1> dxgi_device;
		ComPtr<IDXGIAdapter> dxgi_adapter;
		ComPtr<IDXGIFactory2> dxgi_factory;
		ComPtr<IDXGISwapChain1> swap_chain;
		ComPtr<IDXGISurface> back_buffer;
		ComPtr<ID2D1Bitmap1> target_bitmap;
		ComPtr<ID2D1Effect> blur_effect;
		ComPtr<ID2D1GradientStopCollection> index_background_collection;
		ComPtr<ID2D1GradientStopCollection> description_bar_collection;
		ComPtr<ID2D1GradientStopCollection> file_editor_background_collection;
		ComPtr<ID2D1GradientStopCollection> filename_box_collection;
		ComPtr<ID2D1LinearGradientBrush> index_background_brush;
		ComPtr<ID2D1LinearGradientBrush> description_bar_brush;
		ComPtr<ID2D1LinearGradientBrush> file_editor_background_brush;
		ComPtr<ID2D1LinearGradientBrush> filename_box_brush;
		ComPtr<ID2D1SolidColorBrush> text_brush;
		ComPtr<ID2D1SolidColorBrush> border_brush;
		ComPtr<IDWriteFactory> write_factory;
		ComPtr<IDWriteTextFormat> title_text_format;
		ComPtr<IDWriteTextFormat> normal_text_format;
		D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;
		DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = { 0 };
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreen_desc = { 0 };
		D2D1_BITMAP_PROPERTIES1 bitmap_properties;
		D2D1_GRADIENT_STOP index_stops[2];
		D2D1_GRADIENT_STOP description_bar_stops[3];
		D2D1_GRADIENT_STOP file_editor_background_stops[3];
		D2D1_GRADIENT_STOP filename_box_stops[3];
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
		if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, &feature_level, 1, D3D11_SDK_VERSION, &device, NULL, &device_context)))
		{
			MessageBox(hwnd, L"Create DirectX device failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgi_device)))
		{
			MessageBox(hwnd, L"Query DirectX interface failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), (void**)&factory)))
		{
			MessageBox(hwnd, L"Create DirectX device failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(factory->CreateDevice(dxgi_device.Get(), &device_2d)))
		{
			MessageBox(hwnd, L"Create DirectX device failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(device_2d->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &device_context_2d)))
		{
			MessageBox(hwnd, L"Create DirectX device context failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(dxgi_device->GetAdapter(&dxgi_adapter)))
		{
			MessageBox(hwnd, L"Get DirectX adapter failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(dxgi_adapter->GetParent(IID_PPV_ARGS(&dxgi_factory))))
		{
			MessageBox(hwnd, L"Get DirectX parent object failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		fullscreen_desc.RefreshRate.Numerator = 1;
		fullscreen_desc.RefreshRate.Denominator = 1;
		fullscreen_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		fullscreen_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		fullscreen_desc.Windowed = true;
		swap_chain_desc.Width = client_rect.right - client_rect.left;
		swap_chain_desc.Height = client_rect.bottom - client_rect.top;
		swap_chain_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swap_chain_desc.Stereo = false;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.SampleDesc.Quality = 0;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 2;
		swap_chain_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swap_chain_desc.Scaling = DXGI_SCALING_STRETCH;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.Flags = NULL;
		if (FAILED(dxgi_factory->CreateSwapChainForHwnd(device.Get(), hwnd, &swap_chain_desc, &fullscreen_desc, NULL, &swap_chain)))
		{
			MessageBox(hwnd, L"Create DirectX swap chain failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(dxgi_device->SetMaximumFrameLatency(1)))
		{
			MessageBox(hwnd, L"Set maximum frame latency failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer))))
		{
			MessageBox(hwnd, L"Get DirectX buffer failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		bitmap_properties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), GetDpiForWindow(hwnd), GetDpiForWindow(hwnd));
		if (FAILED(device_context_2d->CreateBitmapFromDxgiSurface(back_buffer.Get(), &bitmap_properties, &target_bitmap)))
		{
			MessageBox(hwnd, L"Create bitmap from DXGI surface failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		device_context_2d->SetTarget(target_bitmap.Get());
		device_context_2d->SetUnitMode(D2D1_UNIT_MODE_PIXELS);
		if (FAILED(device_context_2d->CreateEffect(CLSID_D2D1GaussianBlur, &blur_effect)))
		{
			MessageBox(hwnd, L"Create DirectX effect failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (CurrentMainWindowStatus == INDEX)
		{
			index_stops[0].color = D2D1::ColorF(D2D1::ColorF::Orange);
			index_stops[0].position = 0;
			index_stops[1].color = D2D1::ColorF(D2D1::ColorF::Firebrick);
			index_stops[1].position = 1;
			if (FAILED(device_context_2d->CreateGradientStopCollection(index_stops, 2, &index_background_collection)))
			{
				MessageBox(hwnd, L"Create DirectX gradient stop collection failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.top), D2D1::Point2F(client_rect.right, client_rect.bottom)), index_background_collection.Get(), &index_background_brush)))
			{
				MessageBox(hwnd, L"Create DirectX linear gradient brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
		}
		else
		{
			file_editor_background_stops[0].color = D2D1::ColorF(D2D1::ColorF::SlateGray);
			file_editor_background_stops[0].position = 0;
			file_editor_background_stops[1].color = D2D1::ColorF(D2D1::ColorF::DarkGray);
			file_editor_background_stops[1].position = 0.5;
			file_editor_background_stops[2].color = D2D1::ColorF(D2D1::ColorF::SlateGray);
			file_editor_background_stops[2].position = 1;
			if (FAILED(device_context_2d->CreateGradientStopCollection(file_editor_background_stops, 3, &file_editor_background_collection)))
			{
				MessageBox(hwnd, L"Create DirectX gradient stop collection failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.top), D2D1::Point2F(client_rect.left, client_rect.bottom)), file_editor_background_collection.Get(), &file_editor_background_brush)))
			{
				MessageBox(hwnd, L"Create DirectX linear gradient brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			description_bar_stops[0].color = D2D1::ColorF(D2D1::ColorF::Crimson);
			description_bar_stops[0].position = 0;
			description_bar_stops[1].color = D2D1::ColorF(D2D1::ColorF::OrangeRed);
			description_bar_stops[1].position = 0.5;
			description_bar_stops[2].color = D2D1::ColorF(D2D1::ColorF::Crimson);
			description_bar_stops[2].position = 1;
			if (FAILED(device_context_2d->CreateGradientStopCollection(description_bar_stops, 3, &description_bar_collection)))
			{
				MessageBox(hwnd, L"Create DirectX gradient stop collection failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.bottom-20), D2D1::Point2F(client_rect.right, client_rect.bottom)), description_bar_collection.Get(), &description_bar_brush)))
			{
				MessageBox(hwnd, L"Create DirectX linear gradient brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			filename_box_stops[0].color = D2D1::ColorF(D2D1::ColorF::Purple);
			filename_box_stops[0].position = 0;
			filename_box_stops[1].color = D2D1::ColorF(D2D1::ColorF::Crimson);
			filename_box_stops[1].position = 0.5;
			filename_box_stops[2].color = D2D1::ColorF(D2D1::ColorF::Purple);
			filename_box_stops[2].position = 1;
			if (FAILED(device_context_2d->CreateGradientStopCollection(filename_box_stops, 3, &filename_box_collection)))
			{
				MessageBox(hwnd, L"Create DirectX gradient stop collection failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.bottom - 20), D2D1::Point2F(client_rect.right, client_rect.bottom)), filename_box_collection.Get(), &filename_box_brush)))
			{
				MessageBox(hwnd, L"Create DirectX linear gradient brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Silver), &border_brush)))
			{
				MessageBox(hwnd, L"Create DirectX solid color brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
		}
		if (FAILED(device_context_2d->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &text_brush)))
		{
			MessageBox(hwnd, L"Create DirectX solid color brush failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		device_context_2d->BeginDraw();
		device_context_2d->Clear(D2D1::ColorF(D2D1::ColorF::White));
		switch (CurrentMainWindowStatus)
		{
		case INDEX:
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), index_background_brush.Get());
			device_context_2d->DrawText(L"Welcome to Redstone Designer", wcslen(L"Welcome to Redstone Designer"), title_text_format.Get(), D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.Get());
			device_context_2d->DrawText(L"\n\nChoose a option to continue", wcslen(L"\n\nChoose a option to continue"), normal_text_format.Get(), D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.Get());
			break;
		case FILE_EDITOR:
		{
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), file_editor_background_brush.Get());
			DrawBlockThreadParameters draw_block_param;
			draw_block_param.block_brush = text_brush.Get();
			draw_block_param.block_border_brush = border_brush.Get();
			draw_block_param.device_context = device_context_2d.Get();
			if (CurrentEditingFileName.length() != 0)
			{
				DrawBlocksThread = CreateThread(NULL, 0, DrawBlocks, &draw_block_param, NULL, NULL);
			}
			WaitForSingleObject(DrawBlocksThread, INFINITE);
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left + 4, client_rect.top + 4, client_rect.right - 4, client_rect.top + 26), border_brush.Get());
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left + 5, client_rect.top + 5, client_rect.right - 5, client_rect.top + 25), filename_box_brush.Get());
			device_context_2d->DrawText(CurrentEditingFileName.c_str(), CurrentEditingFileName.length(), normal_text_format.Get(), D2D1::RectF(client_rect.left + 5, client_rect.top + 3, client_rect.right - 5, client_rect.top + 23), text_brush.Get());
			break;
		}
		}
		if (CurrentMainWindowStatus != INDEX)
		{
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.bottom - 20, client_rect.right, client_rect.bottom), description_bar_brush.Get());
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.bottom - 21, client_rect.right, client_rect.bottom - 20), border_brush.Get());
		}
		if (FAILED(device_context_2d->EndDraw()))
		{
			MessageBox(hwnd, L"Drawing failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(swap_chain->Present(true,false)))
		{
			MessageBox(hwnd, L"Present window failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
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
	if (uMsg == WM_ERASEBKGND || uMsg == WM_PAINT)
	{
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		HDC hdc = GetDC(hwnd);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));
		if (CurrentMainWindowStatus == INDEX)
		{
			TextOut(hdc, 0, client_rect.bottom - 31, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 16, L"For testing purposes only. Insider Test 0", wcslen(L"For testing purposes only. Insider Test 0"));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, 0, client_rect.bottom - 33, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 18, L"For testing purposes only. Insider Test 0", wcslen(L"For testing purposes only. Insider Test 0"));
		}
		else
		{
			TextOut(hdc, 0, client_rect.bottom - 55, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 40, L"For testing purposes only. Insider Test 0", wcslen(L"For testing purposes only. Insider Test 0"));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, 0, client_rect.bottom - 57, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 42, L"For testing purposes only. Insider Test 0", wcslen(L"For testing purposes only. Insider Test 0"));
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
	SwitchCursorThread = CreateThread(NULL, 0, SwitchCursorThreadProc, NULL, NULL, NULL);
}

void ApplicationDestructor(HINSTANCE hInstance)
{
	UnregisterClass(L"REDSTONE_DESIGNER", hInstance);
}

void LoadTextures()
{
	D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;
	ComPtr<ID2D1Factory1> factory;
	ComPtr<ID2D1RenderTarget> render_target;
	ComPtr<IWICBitmapDecoder> decoder;
	ComPtr<IWICBitmapFrameDecode> frame_decode;
	ComPtr<IWICStream> stream;
	ComPtr<IWICFormatConverter> converter;
	ComPtr<IWICImagingFactory> imaging_factory;
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), (void**)&factory)))
	{
		MessageBox(NULL, L"Create DirectX device failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if (FAILED(CoCreateInstance(CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&imaging_factory)))
	{
		MessageBox(NULL, L"Create imaging factory failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if (FAILED(imaging_factory->CreateDecoderFromFilename(L"resources/normal_block.bmp", NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder)))
	{
		MessageBox(NULL, L"Create image decoder failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if (FAILED(decoder->GetFrame(0, &frame_decode)))
	{
		MessageBox(NULL, L"Get image frame failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if (FAILED(imaging_factory->CreateFormatConverter(&converter)))
	{
		MessageBox(NULL, L"Create image converter failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if(FAILED(converter->Initialize(frame_decode.Get(),GUID_WICPixelFormat32bppPBGRA,WICBitmapDitherTypeNone,NULL,0,WICBitmapPaletteTypeMedianCut)))
	{
		MessageBox(NULL, L"Initialize image converter failed!\n\nApplication will be terminated.", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
}