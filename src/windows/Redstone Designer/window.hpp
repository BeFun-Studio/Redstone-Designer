#pragma once
#include <Windows.h>
#include <d2d1_3.h>
#include <dxgi1_6.h>
#include <d3d11.h>
#include <dwrite.h>
#include <vector>
#include <wincodec.h>
#include <cuda_extension.cuh>
#include <wrl.h>
#include "api.hpp"
#include "circuit.hpp"
#include "time_check.hpp"
#include "update.hpp"
#include "lang.hpp"
#include "log.hpp"
#include "control.hpp"
#include "asmfuncs.h"
#include "resource.h"
using namespace Microsoft::WRL;

#define WIN32_LEAN_AND_MEAN

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WM_SWITCH_STATUS 10000
#define WM_SET_DESCRIPTION_BAR 10001

#define MENU_BUTTON_CREATE_NEW_FILE_START_PAGE 1000
#define MENU_BUTTON_OPEN_EXISTING_FILE_START_PAGE 1001
#define MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_START_PAGE 1002
#define MENU_BUTTON_ABOUT_WINDOW_OK 1100

enum MAIN_WINDOW_STATUS
{
	START_PAGE=0,
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

MAIN_WINDOW_STATUS CurrentMainWindowStatus = START_PAGE;
WNDCLASS MainWindowClass;
HWND MainWindowHandle;
HWND AboutWindowHandle = NULL;
unsigned char BlockViewSize = 75;
CircuitLayer *CurrentLayer;
Position CurrentViewingPosition;
wstring CurrentEditingFileName;
vector<HWND>buttons;
vector<HWND>edits;
vector<HWND>editors;
wstring MainWindowDescriptionBarText;

HWND AboutWindowOkayButton;

int PhysicalMemorySize;
int ProcessUsedMemorySize;

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

list<Block*>SelectedBlocks;
vector<Component*>SelectedComponents;

HINSTANCE ApplicationInstance;

HANDLE ShowUpdateAvailableTitleThread;
HANDLE CheckUpdateAvailableFlagThread;
HANDLE PlayPleaseWaitAnimationThread;
HANDLE AboutWindowThread;

HANDLE DrawBlocksThread;
HANDLE DrawRedstoneBlocksThread;

HFONT ShowPleaseWaitAnimationFont;
const HFONT ControlFont = _CreateFont(19, L"Unifont", false, false, false);

bool CudaSpeedupEnabled = false;
bool OpenCLSpeedupEnabled = false;

bool UserSpecifiedApplicationExit = false;

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
ComPtr<IDWriteFactory> write_factory;
ComPtr<IDWriteTextFormat> title_text_format;
ComPtr<IDWriteTextFormat> normal_text_format;

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

bool AboutWindowClassRegistered = false;

struct DrawingThreadParameters
{
	ID2D1DeviceContext* device_context;
};

struct DrawBlockThreadParameters :public DrawingThreadParameters
{
	ID2D1SolidColorBrush* block_brush;
	ID2D1SolidColorBrush* block_border_brush;
};

void NewCircuitFile(LPCWSTR file_name)
{
	CircuitLayer push_layer;
	CircuitLayers.push_back(push_layer);
	CurrentLayer = &CircuitLayers.back();
	Block init_block;
	for(signed char i=-4;i<=4;i++)
		for (signed char j = -4; j <= 4; j++)
		{
			init_block.SetPosition(i, j);
			CurrentLayer->blocks.push_back(init_block);
		}
	CurrentViewingPosition = { 0,0 };
	CurrentEditingFileName = file_name;
}

DWORD WINAPI ShowUpdateAvailableTitleThreadProc(LPVOID lpParameter)
{
	while(true)
	{
		SetWindowText(MainWindowHandle, L"Redstone Designer [Update Available]");
		Sleep(1000);
		SetWindowText(MainWindowHandle, L"Redstone Designer");
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI CheckUpdateAvailableFlagThreadProc(LPVOID lpParameter)
{
	if (IsUpdateAvailable())
	{
		ShowUpdateAvailableTitleThread = CreateThread(NULL, 0, ShowUpdateAvailableTitleThreadProc, NULL, NULL, NULL);
	}
	return 0;
}

LRESULT WINAPI AboutWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case MENU_BUTTON_CREATE_NEW_FILE_START_PAGE:
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_PAINT:
	{
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		ComPtr<ID2D1Factory>factory;
		ComPtr<IDWriteFactory>write_factory;
		ComPtr<IDWriteTextFormat>title_format;
		ComPtr<IDWriteTextFormat>text_format;
		ComPtr<ID2D1HwndRenderTarget>render_target;
		ComPtr<ID2D1GradientStopCollection>background_gradient_stop_collection;
		ComPtr<ID2D1GradientStopCollection>separator_gradient_stop_collection;
		ComPtr<ID2D1LinearGradientBrush>background_brush;
		ComPtr<ID2D1LinearGradientBrush>separator_brush;
		ComPtr<ID2D1SolidColorBrush>text_brush;
		D2D1_GRADIENT_STOP background_stops[2];
		D2D1_GRADIENT_STOP separator_stops[3];
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,__uuidof(ID2D1Factory),&factory)))
		{
			MessageBox(MainWindowHandle, CreateDirect2DFactoryFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), &write_factory)))
		{
			MessageBox(MainWindowHandle, CreateDirectWriteFactoryFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(write_factory->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 25, L"", &title_format)))
		{
			MessageBox(MainWindowHandle, CreateDirectWriteTextFormatFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(write_factory->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 18, L"", &text_format)))
		{
			MessageBox(MainWindowHandle, CreateDirectWriteTextFormatFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(client_rect.right - client_rect.left, client_rect.bottom - client_rect.top)), &render_target)))
		{
			MessageBox(MainWindowHandle, CreateDirect2DRenderTargetFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		background_stops[0].color = D2D1::ColorF(D2D1::ColorF::RoyalBlue);
		background_stops[0].position = 0.5;
		background_stops[1].color = D2D1::ColorF(D2D1::ColorF::Aqua);
		background_stops[1].position = 1.0;
		separator_stops[0].color = D2D1::ColorF(D2D1::ColorF::SkyBlue);
		separator_stops[0].position = 0.2;
		separator_stops[1].color = D2D1::ColorF(D2D1::ColorF::Azure);
		separator_stops[1].position = 0.5;
		separator_stops[2].color = D2D1::ColorF(D2D1::ColorF::SkyBlue);
		separator_stops[2].position = 1.0;
		if (FAILED(render_target->CreateGradientStopCollection(background_stops, 2, &background_gradient_stop_collection)))
		{
			MessageBox(MainWindowHandle, CreateDirect2DGradientStopCollectionFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(render_target->CreateGradientStopCollection(separator_stops, 3, &separator_gradient_stop_collection)))
		{
			MessageBox(MainWindowHandle, CreateDirect2DGradientStopCollectionFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(render_target->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.top), D2D1::Point2F(client_rect.left, client_rect.bottom)), background_gradient_stop_collection.Get(), &background_brush)))
		{
			MessageBox(MainWindowHandle, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(render_target->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.top), D2D1::Point2F(client_rect.right, client_rect.top)), separator_gradient_stop_collection.Get(), &separator_brush)))
		{
			MessageBox(MainWindowHandle, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &text_brush)))
		{
			MessageBox(MainWindowHandle, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		render_target->BeginDraw();
		render_target->FillRectangle(D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), background_brush.Get());
		render_target->DrawText(L"About Redstone Designer", wcslen(L"About Redstone Designer"), title_format.Get(), D2D1::RectF(client_rect.left + 5, client_rect.top, client_rect.right - 5, client_rect.top + 30), text_brush.Get());
		render_target->DrawText(L"Copyright(C)2020 CodesBuilder", wcslen(L"Copyright(C)2020 CodesBuilder"), text_format.Get(), D2D1::RectF(client_rect.left + 5, client_rect.top + 30, client_rect.right - 5, client_rect.top + 50), text_brush.Get());
		render_target->FillRectangle(D2D1::RectF(client_rect.left+5, client_rect.top + 54, client_rect.right-5, client_rect.top + 56), separator_brush.Get());
		if (FAILED(render_target->EndDraw()))
		{
			MessageBox(MainWindowHandle, DrawWindowContentsFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		break;
	}
	case WM_CREATE:
	{
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		AboutWindowOkayButton = CreateWindow(L"__NORMAL_BUTTON__", L"OK", WS_CHILD | WS_VISIBLE, client_rect.right - 100, client_rect.bottom - 40, 90, 30, hwnd, (HMENU)MENU_BUTTON_CREATE_NEW_FILE_START_PAGE, ApplicationInstance, NULL);
		SendMessage(AboutWindowOkayButton, WM_CTLCOLORBTN, (WPARAM)RGB(200,175,0), NULL);
		break;
	}
	case WM_DESTROY:
		DestroyWindow(AboutWindowOkayButton);
		AboutWindowHandle = NULL;
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void InitAboutWindow()
{
	if (!AboutWindowClassRegistered)
	{
		WNDCLASS about_window_class = { 0 };
		about_window_class.hCursor = LoadCursor(ApplicationInstance, (LPCWSTR)IDC_ARROW);
		about_window_class.lpszClassName = L"ABOUT_REDSTONE_DESIGNER";
		about_window_class.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		about_window_class.hIcon = LoadIcon(ApplicationInstance, (LPCWSTR)IDI_REDSTONE_TOOLS);
		about_window_class.lpfnWndProc = AboutWindowProc;
		if (RegisterClass(&about_window_class) == NULL)
		{
			MessageBox(MainWindowHandle, L"Register window class failed!\nApplication will be terminated", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
		}
		AboutWindowClassRegistered = true;
	}
	if (AboutWindowHandle != NULL)
		DestroyWindow(AboutWindowHandle);
	AboutWindowHandle = CreateWindowEx(WS_EX_TOOLWINDOW, L"ABOUT_REDSTONE_DESIGNER", L"About Redstone Designer", WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, MainWindowHandle, NULL, ApplicationInstance, NULL);
	if (AboutWindowHandle == NULL)
	{
		MessageBox(MainWindowHandle, L"Create window failed!\nApplication will be terminated", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	ShowWindow(AboutWindowHandle, SW_SHOW);
}

DWORD WINAPI DrawBlocks(LPVOID lpParameter)
{
	ShowedBlocks.clear();
	ShowedBlocks.shrink_to_fit();
	DrawBlockThreadParameters* parameters = (DrawBlockThreadParameters*)lpParameter;
	ComPtr<ID2D1SolidColorBrush> selected_border_brush;
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
		ComPtr<ID2D1SolidColorBrush> tmp_brush;
		for (list<Block*>::iterator iter=SelectedBlocks.begin();iter!=SelectedBlocks.end();iter++)
			if (*itor == **iter)
			{
				if (FAILED(parameters->device_context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &selected_border_brush)))
				{
					MessageBox(MainWindowHandle, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
					PostQuitMessage(1);
				}
				tmp_brush = parameters->block_border_brush;
				parameters->block_border_brush = selected_border_brush.Get();
				break;
			}
		parameters->device_context->FillRectangle(D2D1::RectF(start_draw_position.x - BlockViewSize / 2, start_draw_position.y - BlockViewSize / 2, start_draw_position.x + BlockViewSize / 2, start_draw_position.y + BlockViewSize / 2), parameters->block_border_brush);
		parameters->device_context->FillRectangle(D2D1::RectF(start_draw_position.x - BlockViewSize / 2 + 2, start_draw_position.y - BlockViewSize / 2 + 2, start_draw_position.x + BlockViewSize / 2 - 2, start_draw_position.y + BlockViewSize / 2 - 2), parameters->block_brush);
		if (tmp_brush != NULL)
			parameters->block_border_brush = tmp_brush.Get();
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
		case MENU_BUTTON_CREATE_NEW_FILE_START_PAGE:
		{
			NewCircuitFile(L"Untitled.rsd");
			SendMessage(hwnd, WM_SWITCH_STATUS, FILE_EDITOR, NULL);
			break;
		}
		case MENU_BUTTON_OPEN_EXISTING_FILE_START_PAGE:
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
		case MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_START_PAGE:
			SendMessage(hwnd, WM_SWITCH_STATUS, FILE_EDITOR, NULL);
			RECT client_rect;
			GetClientRect(hwnd, &client_rect);
			InvalidateRect(hwnd, &client_rect, false);
			break;
		case ID_NEW_CIRCUITFILE:
			SendMessage(hwnd, WM_COMMAND, MENU_BUTTON_CREATE_NEW_FILE_START_PAGE, NULL);
			break;
		case ID_FILE_OPEN:
			SendMessage(hwnd, WM_COMMAND, MENU_BUTTON_OPEN_EXISTING_FILE_START_PAGE, NULL);
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
		WriteLog(L"Switching main window status...");
		WriteLog(L"Destroying windows...");
		for (int i = 0; i < buttons.size(); i++)
			DestroyWindow(buttons[i]);
		buttons.clear();
		buttons.shrink_to_fit();
		for (int i = 0; i < edits.size(); i++)
			DestroyWindow(edits[i]);
		edits.clear();
		edits.shrink_to_fit();
		WriteLog(L"Destroy windows successfully.");
		switch ((unsigned char)wParam)
		{
		case START_PAGE:
		{
			WriteLog(L"Switching main window's status, target status:start page");
			WriteLog(L"Creating windows...");
			buttons.push_back(CreateWindow(L"__NORMAL_BUTTON__", ContinueAndCreateANewFileButtonText.c_str(), WS_CHILD | WS_VISIBLE, 10, 80, 360, 50, hwnd, (HMENU)MENU_BUTTON_CREATE_NEW_FILE_START_PAGE, ApplicationInstance, NULL));
			buttons.push_back(CreateWindow(L"__NORMAL_BUTTON__", ContinueAndOpenExistingFileButtonText.c_str(), WS_CHILD | WS_VISIBLE, 10, 140, 360, 50, hwnd, (HMENU)MENU_BUTTON_OPEN_EXISTING_FILE_START_PAGE, ApplicationInstance, NULL));
			buttons.push_back(CreateWindow(L"__NORMAL_BUTTON__", ContinueWithoutAnyOperationButtonText.c_str(), WS_CHILD | WS_VISIBLE, 10, 200, 360, 50, hwnd, (HMENU)MENU_BUTTON_CONTINUE_WITHOUT_ANY_OPERATION_START_PAGE, ApplicationInstance, NULL));
			for (int i = 0; i < buttons.size(); i++)
			{
				ShowWindow(buttons[i], SW_SHOW);
				SendMessage(buttons[i], WM_CTLCOLORBTN, (WPARAM)RGB(50, 50, 200), NULL);
			}
			WriteLog(L"Create windows successfully.");
			CurrentMainWindowStatus = START_PAGE;
			break;
		}
		case FILE_EDITOR:
		{
			WriteLog(L"Switching main window's status, target status:file editor");
			CurrentMainWindowStatus = FILE_EDITOR;
			WriteLog(L"Setting text of description bar...");
			SendMessage(hwnd, WM_SET_DESCRIPTION_BAR, (WPARAM)DescriptionBarNoItemsSelectedText.c_str(), NULL);
			WriteLog(L"Setting text of description bar successfully.");
			break;
		}
		}
		WriteLog(L"Switch main window's status successfully.");
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			WriteLog(L"User specified exit the application.");
			if (MessageBox(hwnd, L"Are you sure want to exit?\nAll changes will not be saved!", L"Exit?", MB_YESNO | MB_ICONWARNING) == IDYES)
				PostQuitMessage(0);
			WriteLog(L"User canceled the exit command.");
		}
		break;
	case WM_LBUTTONDOWN:
	{
		if (CurrentMainWindowStatus != FILE_EDITOR)
			break;
		SelectedBlocks.clear();
		short mouse_x = LOWORD(lParam);
		short mouse_y = HIWORD(lParam);
		for (int i = 0; i < ShowedBlocks.size(); i++)
			if (mouse_x >= ShowedBlocks[i].owned_area.left && mouse_y >= ShowedBlocks[i].owned_area.top && mouse_x <= ShowedBlocks[i].owned_area.right && mouse_y <= ShowedBlocks[i].owned_area.bottom)
			{
				SelectedBlocks.push_back(ShowedBlocks[i].block);
				break;
			}
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		InvalidateRect(hwnd, &client_rect, false);
		break;
	}
	case WM_PAINT:
	{
		WriteLog(L"Get a paint request. Preparing for painting...");
		/* Prepares for paint process. */
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		/* Direct2D resources.*/
		ComPtr<ID2D1Effect> blur_effect;
		ComPtr<ID2D1GradientStopCollection> START_PAGE_background_collection;
		ComPtr<ID2D1GradientStopCollection> description_bar_collection;
		ComPtr<ID2D1GradientStopCollection> file_editor_background_collection;
		ComPtr<ID2D1GradientStopCollection> filename_box_collection;
		ComPtr<ID2D1LinearGradientBrush> START_PAGE_background_brush;
		ComPtr<ID2D1LinearGradientBrush> description_bar_brush;
		ComPtr<ID2D1LinearGradientBrush> file_editor_background_brush;
		ComPtr<ID2D1LinearGradientBrush> filename_box_brush;
		ComPtr<ID2D1SolidColorBrush> text_brush;
		ComPtr<ID2D1SolidColorBrush> border_brush;
		DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = { 0 };
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreen_desc = { 0 };
		D2D1_BITMAP_PROPERTIES1 bitmap_properties;
		D2D1_GRADIENT_STOP START_PAGE_stops[2];
		D2D1_GRADIENT_STOP description_bar_stops[3];
		D2D1_GRADIENT_STOP file_editor_background_stops[3];
		D2D1_GRADIENT_STOP filename_box_stops[3];
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
		WriteLog(L"Creating swap chain...");
		if (FAILED(dxgi_factory->CreateSwapChainForHwnd(device.Get(), hwnd, &swap_chain_desc, &fullscreen_desc, NULL, &swap_chain)))
		{
			WriteLog(L"Creating swap chain failed!Application will be terminated.");
			MessageBox(hwnd, CreateDirect2DSwapChainObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		WriteLog(L"Create swap chain successfully.");
		WriteLog(L"Getting buffer of swap chain...");
		if (FAILED(swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer))))
		{
			WriteLog(L"Get buffer of swap chain failed!Application will be terminated.");
			MessageBox(hwnd, GetDirect2DBufferObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		bitmap_properties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), GetDpiForWindow(hwnd), GetDpiForWindow(hwnd));
		WriteLog(L"Get buffer of swap chain successfully.");
		WriteLog(L"Creating bitmap from DXGI surface...");
		if (FAILED(device_context_2d->CreateBitmapFromDxgiSurface(back_buffer.Get(), &bitmap_properties, &target_bitmap)))
		{
			WriteLog(L"Create bitmap from DXGI surface failed!Application will be terminated.");
			MessageBox(hwnd, CreateDirect2DBitmapFromDXGISurfaceObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		WriteLog(L"Create bitmap from DXGI surface successfully.");
		device_context_2d->SetTarget(target_bitmap.Get());
		device_context_2d->SetUnitMode(D2D1_UNIT_MODE_PIXELS);
		WriteLog(L"Creating Direct2D resources...");
		if (FAILED(device_context_2d->CreateEffect(CLSID_D2D1GaussianBlur, &blur_effect)))
		{
			WriteLog(L"Create Direct2D effect object failed!Application will be terminated.");
			MessageBox(hwnd, CreateDirect2DEffectObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (CurrentMainWindowStatus == START_PAGE)
		{
			START_PAGE_stops[0].color = D2D1::ColorF(RGB(110, 110, 255));
			START_PAGE_stops[0].position = 0;
			START_PAGE_stops[1].color = D2D1::ColorF(D2D1::ColorF::Firebrick);
			START_PAGE_stops[1].position = 1;
			if (FAILED(device_context_2d->CreateGradientStopCollection(START_PAGE_stops, 2, &START_PAGE_background_collection)))
			{
				MessageBox(hwnd, CreateDirect2DGradientStopCollectionFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.top), D2D1::Point2F(client_rect.left, client_rect.bottom)), START_PAGE_background_collection.Get(), &START_PAGE_background_brush)))
			{
				MessageBox(hwnd, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
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
				MessageBox(hwnd, CreateDirect2DGradientStopCollectionFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.top), D2D1::Point2F(client_rect.left, client_rect.bottom)), file_editor_background_collection.Get(), &file_editor_background_brush)))
			{
				MessageBox(hwnd, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
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
				MessageBox(hwnd, CreateDirect2DGradientStopCollectionFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.bottom-20), D2D1::Point2F(client_rect.right, client_rect.bottom)), description_bar_collection.Get(), &description_bar_brush)))
			{
				MessageBox(hwnd, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
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
				MessageBox(hwnd, CreateDirect2DGradientStopCollectionFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(client_rect.left, client_rect.bottom - 20), D2D1::Point2F(client_rect.right, client_rect.bottom)), filename_box_collection.Get(), &filename_box_brush)))
			{
				MessageBox(hwnd, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(device_context_2d->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Silver), &border_brush)))
			{
				MessageBox(hwnd, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
		}
		if (FAILED(device_context_2d->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &text_brush)))
		{
			MessageBox(hwnd, CreateDirect2DBrushFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		WriteLog(L"Create Direct2D resources successfully.");
		device_context_2d->BeginDraw();
		WriteLog(L"Starting to draw window contents...");
		device_context_2d->Clear(D2D1::ColorF(D2D1::ColorF::White));
		switch (CurrentMainWindowStatus)
		{
		case START_PAGE:
		{
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), START_PAGE_background_brush.Get());
			device_context_2d->DrawText(WelcomeText.c_str(), wcslen(WelcomeText.c_str()), title_text_format.Get(), D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.Get());
			device_context_2d->DrawText((L"\n\n" + SelectAOptionToContinueText).c_str(), wcslen((L"\n\n" + SelectAOptionToContinueText).c_str()), normal_text_format.Get(), D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.Get());
			break;
		}
		case FILE_EDITOR:
		{
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), file_editor_background_brush.Get());
			DrawBlockThreadParameters draw_block_param;
			draw_block_param.block_brush = text_brush.Get();
			draw_block_param.block_border_brush = border_brush.Get();
			draw_block_param.device_context = device_context_2d.Get();
			WriteLog(L"Detecting blocks...");
			if (CurrentEditingFileName.length() != 0)
			{
				WriteLog(L"Blocks detected. Starting drawing task...");
				DrawBlocksThread = CreateThread(NULL, 1, DrawBlocks, &draw_block_param, NULL, NULL);
			}
			AllocateTaskToCpuCore(0, DrawBlocksThread);
			WaitForSingleObject(DrawBlocksThread, INFINITE);
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left + 4, client_rect.top + 4, client_rect.right - 4, client_rect.top + 26), border_brush.Get());
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left + 5, client_rect.top + 5, client_rect.right - 5, client_rect.top + 25), filename_box_brush.Get());
			device_context_2d->DrawText(CurrentEditingFileName.c_str(), CurrentEditingFileName.length(), normal_text_format.Get(), D2D1::RectF(client_rect.left + 5, client_rect.top + 3, client_rect.right - 5, client_rect.top + 23), text_brush.Get());
			break;
		}
		}
		if (CurrentMainWindowStatus != START_PAGE)
		{
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.bottom - 20, client_rect.right, client_rect.bottom), description_bar_brush.Get());
			device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.bottom - 21, client_rect.right, client_rect.bottom - 20), border_brush.Get());
			device_context_2d->DrawText(MainWindowDescriptionBarText.c_str(), MainWindowDescriptionBarText.length(), normal_text_format.Get(), D2D1::RectF(client_rect.left, client_rect.bottom - 21, client_rect.right, client_rect.bottom - 1), text_brush.Get());
		}
		if (FAILED(device_context_2d->EndDraw()))
		{
			MessageBox(hwnd, DrawWindowContentsFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(swap_chain->Present(true,false)))
		{
			MessageBox(hwnd, PresentWindowContentsFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		break;
	}
	case WM_CREATE:
	{
		D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;
		if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&write_factory)))
		{
			MessageBox(hwnd, CreateDirectWriteFactoryFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(write_factory->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"", &title_text_format)))
		{
			MessageBox(hwnd, CreateDirectWriteTextFormatFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(write_factory->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 18, L"", &normal_text_format)))
		{
			MessageBox(hwnd, CreateDirectWriteTextFormatFailedText.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, &feature_level, 1, D3D11_SDK_VERSION, &device, NULL, &device_context)))
		{
			MessageBox(hwnd, CreateDirect3DDeviceObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgi_device)))
		{
			MessageBox(hwnd, L"Query DirectX interface failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), (void**)&factory)))
		{
			MessageBox(hwnd, L"Create DirectX device failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(factory->CreateDevice(dxgi_device.Get(), &device_2d)))
		{
			MessageBox(hwnd, L"Create DirectX device failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(device_2d->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &device_context_2d)))
		{
			MessageBox(hwnd, L"Create DirectX device context failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(dxgi_device->GetAdapter(&dxgi_adapter)))
		{
			MessageBox(hwnd, GetDXGIAdapterObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(dxgi_adapter->GetParent(IID_PPV_ARGS(&dxgi_factory))))
		{
			MessageBox(hwnd, GetDXGIParentObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
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
		SelectObject(hdc, ControlFont);
		if (CurrentMainWindowStatus == START_PAGE)
		{
			TextOut(hdc, 0, client_rect.bottom - 33, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 17, ((wstring)ForTestingPurposesOnlyText + L" Insider Test 0").c_str(), wcslen(((wstring)ForTestingPurposesOnlyText + L" Insider Test 0").c_str()));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, 0, client_rect.bottom - 35, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 19, ((wstring)ForTestingPurposesOnlyText + L" Insider Test 0").c_str(), wcslen(((wstring)ForTestingPurposesOnlyText + L" Insider Test 0").c_str()));
		}
		else
		{
			TextOut(hdc, 0, client_rect.bottom - 58, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 41, ((wstring)ForTestingPurposesOnlyText + L" Insider Test 0").c_str(), wcslen(((wstring)ForTestingPurposesOnlyText + L" Insider Test 0").c_str()));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, 0, client_rect.bottom - 60, L"Redstone Designer Codename 'Emerald'", wcslen(L"Redstone Designer Codename 'Emerald'"));
			TextOut(hdc, 0, client_rect.bottom - 43, ((wstring)ForTestingPurposesOnlyText + L" Insider Test 0").c_str(), wcslen(((wstring)ForTestingPurposesOnlyText + L" Insider Test 0").c_str()));
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
	MainWindowClass.hCursor = LoadCursor(ApplicationInstance, (LPCWSTR)IDC_ARROW);
	MainWindowClass.hIcon = LoadIcon(hInstance, (LPCWSTR)IDI_LOGO);
	MainWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	MainWindowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	WriteLog(L"Registering main window class...");
	if (RegisterClass(&MainWindowClass) == NULL)
	{
		WriteLog(L"Register main window class failed!Application will be terminated.");
		MessageBox(NULL, L"Register Window Class Failed!", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(1);
	}
	WriteLog(L"Create window class successfully.");
	WriteLog(L"Creating main window...");
	switch (GlobalLanguage)
	{
	case ENGLISH:
		MainWindowHandle = CreateWindow(L"REDSTONE_DESIGNER", L"Redstone Designer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, LoadMenuW(ApplicationInstance, (LPCWSTR)IDR_MENU_ENGLISH), hInstance, NULL);
		break;
	case CHINESE_SIMPLIFIED:
		MainWindowHandle = CreateWindow(L"REDSTONE_DESIGNER", L"Redstone Designer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, LoadMenuW(ApplicationInstance, (LPCWSTR)IDR_MENU_CHINESE_SIMPLIFIED), hInstance, NULL);
		break;
	default:
		throw InvalidLanguage();
	}
	if (MainWindowHandle == NULL)
	{
		WriteLog(L"Create window failed!Application will be terminated.");
		MessageBox(NULL, L"Create window failed!", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		exit(1);
	}
	WriteLog(L"Create window successfully.");
	ShowWindow(MainWindowHandle, SW_SHOW);
	SendMessage(MainWindowHandle, WM_SWITCH_STATUS, (WPARAM)hInstance, NULL);
	WriteLog(L"Creating threads...");
	CheckUpdateAvailableFlagThread = CreateThread(NULL, 0, CheckUpdateAvailableFlagThreadProc, NULL, NULL, NULL);
	WriteLog(L"Create threads successfully.");
}

void ApplicationDestructor(HINSTANCE hInstance)
{
	if(AboutWindowClassRegistered)
		UnregisterClass(L"ABOUT_REDSTONE_DESIGNER", hInstance);
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
		MessageBox(NULL, L"Create DirectX device failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if (FAILED(CoCreateInstance(CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&imaging_factory)))
	{
		MessageBox(NULL, L"Create imaging factory failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if (FAILED(imaging_factory->CreateDecoderFromFilename(L"resources/normal_block.bmp", NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder)))
	{
		MessageBox(NULL, L"Create image decoder failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if (FAILED(decoder->GetFrame(0, &frame_decode)))
	{
		MessageBox(NULL, L"Get image frame failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if (FAILED(imaging_factory->CreateFormatConverter(&converter)))
	{
		MessageBox(NULL, L"Create image converter failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
	if(FAILED(converter->Initialize(frame_decode.Get(),GUID_WICPixelFormat32bppPBGRA,WICBitmapDitherTypeNone,NULL,0,WICBitmapPaletteTypeMedianCut)))
	{
		MessageBox(NULL, L"Initialize image converter failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
		PostQuitMessage(1);
	}
}