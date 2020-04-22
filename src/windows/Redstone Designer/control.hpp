#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <wrl.h>
#include <list>
using namespace std;
using namespace Microsoft::WRL;

/* Application's instance handle. */
extern HINSTANCE ApplicationInstance;

/* Exceptions. */
class RegisterControlsFailed
{
};
class InitializationControlFailed
{
};
class PaintControlFailed
{
};

/* Control relation structures. */
struct BasicControlRelationUnit
{
	HWND hwnd;
	COLORREF background_color;
	COLORREF background_color_backup;
	COLORREF foreground_color;
	bool pushed;
};

struct BasicControlPaintUnit
{
	bool mouse_hovered;
	bool resource_created;
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
	ComPtr<IDWriteFactory>write_factory;
	ComPtr<IDWriteTextFormat>text_format;
	D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = { 0 };
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreen_desc = { 0 };
	D2D1_BITMAP_PROPERTIES1 bitmap_properties;
	HWND hwnd;
};

list<BasicControlRelationUnit> __normal_button_relation_unit_table__;
list<BasicControlPaintUnit>__normal_button_paint_unit_table__;

LRESULT CALLBACK NormalButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		UpdateWindow(hwnd);
		break;
	case WM_MOUSEHOVER:
	{
		for (list<BasicControlPaintUnit>::iterator iter = __normal_button_paint_unit_table__.begin(); iter != __normal_button_paint_unit_table__.end(); iter++)
			if (iter->hwnd == hwnd)
			{
				if (!iter->mouse_hovered)
					for (list<BasicControlRelationUnit>::iterator itor = __normal_button_relation_unit_table__.begin(); itor != __normal_button_relation_unit_table__.end(); itor++)
						if (itor->hwnd == hwnd)
						{
							unsigned char current_r = GetRValue(itor->background_color);
							unsigned char current_g = GetGValue(itor->background_color);
							unsigned char current_b = GetBValue(itor->background_color);
							if (current_r + 30 >= 255)
								current_r = 255;
							else
								current_r += 30;
							if (current_g + 30 >= 255)
								current_g = 255;
							else
								current_g += 30;
							if (current_b + 30 >= 255)
								current_b = 255;
							else
								current_b += 30;
							itor->background_color = RGB(current_r, current_g, current_b);
							RECT client_rect;
							GetClientRect(hwnd, &client_rect);
							InvalidateRect(hwnd, &client_rect, false);
							iter->mouse_hovered = true;
						}
			}
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 0;
		tme.hwndTrack = hwnd;
		TrackMouseEvent(&tme);
		break;
	}
	case WM_CTLCOLORBTN:
		for (list<BasicControlRelationUnit>::iterator itor = __normal_button_relation_unit_table__.begin(); itor != __normal_button_relation_unit_table__.end(); itor++)
			if (itor->hwnd == hwnd)
			{
				itor->background_color = wParam;
				itor->background_color_backup = wParam;
				if (GetRValue(itor->foreground_color) > 127 && GetGValue(itor->foreground_color) > 127 && GetBValue(itor->foreground_color) > 127)
					itor->foreground_color = RGB(0, 0, 0);
				else
					itor->foreground_color = RGB(255, 255, 255);
				break;
			}
		break;
	case WM_MOUSELEAVE:
	{
		for (list<BasicControlPaintUnit>::iterator itor = __normal_button_paint_unit_table__.begin(); itor != __normal_button_paint_unit_table__.end(); itor++)
			if (itor->hwnd == hwnd)
			{
				itor->mouse_hovered = false;
				break;
			}
		UpdateWindow(hwnd);
		for (list<BasicControlRelationUnit>::iterator itor = __normal_button_relation_unit_table__.begin(); itor != __normal_button_relation_unit_table__.end(); itor++)
			if (itor->hwnd == hwnd)
			{
				itor->background_color = itor->background_color_backup;
				RECT client_rect;
				itor->pushed = false;
				GetClientRect(hwnd, &client_rect);
				InvalidateRect(hwnd, &client_rect, false);
			}
		break;
	}
	case WM_LBUTTONUP:
		for (list<BasicControlRelationUnit>::iterator itor = __normal_button_relation_unit_table__.begin(); itor != __normal_button_relation_unit_table__.end(); itor++)
			if (itor->hwnd == hwnd)
			{
				if (itor->pushed)
					SendMessage(GetParent(hwnd), WM_COMMAND, (WPARAM)GetMenu(hwnd), NULL);
				break;
			}
		break;
	case WM_LBUTTONDOWN:
		for (list<BasicControlRelationUnit>::iterator itor = __normal_button_relation_unit_table__.begin(); itor != __normal_button_relation_unit_table__.end(); itor++)
			if (itor->hwnd == hwnd)
			{
				itor->pushed = true;
				RECT client_rect;
				GetClientRect(hwnd, &client_rect);
				InvalidateRect(hwnd, &client_rect, false);
				break;
			}
		break;
	case WM_MOUSEMOVE:
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 0;
		tme.hwndTrack = hwnd;
		TrackMouseEvent(&tme);
		SendMessage(hwnd, WM_MOUSEHOVER, NULL, NULL);
		break;
	}
	case WM_PAINT:
	{
		ComPtr<ID2D1SolidColorBrush>text_brush;
		ComPtr<ID2D1GradientStopCollection>gradient_stop_collection;
		ComPtr<ID2D1SolidColorBrush>border_brush;
		ComPtr<ID2D1LinearGradientBrush>linear_gradient_brush;
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		list<BasicControlPaintUnit>::iterator iter;
		for (list<BasicControlPaintUnit>::iterator itor = __normal_button_paint_unit_table__.begin(); itor != __normal_button_paint_unit_table__.end(); itor++)
			if (itor->hwnd == hwnd)
				iter = itor;
		if (!iter->resource_created)
		{
			if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, &iter->feature_level, 1, D3D11_SDK_VERSION, &iter->device, NULL, &iter->device_context)))
			{
				MessageBox(hwnd, CreateDirect3DDeviceObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(iter->device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&iter->dxgi_device)))
			{
				MessageBox(hwnd, L"Query DirectX interface failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), (void**)&iter->factory)))
			{
				MessageBox(hwnd, L"Create DirectX device failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(iter->factory->CreateDevice(iter->dxgi_device.Get(), &iter->device_2d)))
			{
				MessageBox(hwnd, L"Create DirectX device failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(iter->device_2d->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &iter->device_context_2d)))
			{
				MessageBox(hwnd, L"Create DirectX device context failed!\n\nApplication will be terminated.", ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(iter->dxgi_device->GetAdapter(&iter->dxgi_adapter)))
			{
				MessageBox(hwnd, GetDXGIAdapterObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			if (FAILED(iter->dxgi_adapter->GetParent(IID_PPV_ARGS(&iter->dxgi_factory))))
			{
				MessageBox(hwnd, GetDXGIParentObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
				PostQuitMessage(1);
			}
			iter->fullscreen_desc.RefreshRate.Numerator = 1;
			iter->fullscreen_desc.RefreshRate.Denominator = 1;
			iter->fullscreen_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			iter->fullscreen_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			iter->fullscreen_desc.Windowed = true;
			iter->swap_chain_desc.Width = client_rect.right - client_rect.left;
			iter->swap_chain_desc.Height = client_rect.bottom - client_rect.top;
			iter->swap_chain_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			iter->swap_chain_desc.Stereo = false;
			iter->swap_chain_desc.SampleDesc.Count = 1;
			iter->swap_chain_desc.SampleDesc.Quality = 0;
			iter->swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			iter->swap_chain_desc.BufferCount = 2;
			iter->swap_chain_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			iter->swap_chain_desc.Scaling = DXGI_SCALING_STRETCH;
			iter->swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			iter->swap_chain_desc.Flags = NULL;
			if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), &iter->write_factory)))
			{
				throw PaintControlFailed();
				break;
			}
			if (FAILED(iter->write_factory->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"", &iter->text_format)))
			{
				throw PaintControlFailed();
				break;
			}
			iter->text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			iter->resource_created = true;
		}
		if (FAILED(iter->dxgi_factory->CreateSwapChainForHwnd(iter->device.Get(), hwnd, &iter->swap_chain_desc, &iter->fullscreen_desc, NULL, &iter->swap_chain)))
		{
			MessageBox(hwnd, CreateDirect2DSwapChainObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		if (FAILED(iter->swap_chain->GetBuffer(0, IID_PPV_ARGS(&iter->back_buffer))))
		{
			MessageBox(hwnd, GetDirect2DBufferObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		iter->bitmap_properties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), GetDpiForWindow(hwnd), GetDpiForWindow(hwnd));
		if (FAILED(iter->device_context_2d->CreateBitmapFromDxgiSurface(iter->back_buffer.Get(), &iter->bitmap_properties, &iter->target_bitmap)))
		{
			MessageBox(hwnd, CreateDirect2DBitmapFromDXGISurfaceObjectFailed.c_str(), ErrorWindowCaption.c_str(), MB_OK | MB_ICONERROR);
			PostQuitMessage(1);
		}
		iter->device_context_2d->SetTarget(iter->target_bitmap.Get());
		iter->device_context_2d->SetUnitMode(D2D1_UNIT_MODE_PIXELS);
		iter->device_context_2d->BeginDraw();
		COLORREF bg_color;
		COLORREF fg_color;
		unsigned char middle_color_r;
		unsigned char middle_color_g;
		unsigned char middle_color_b;
		bool pushed;
		for(list<BasicControlRelationUnit>::iterator itor=__normal_button_relation_unit_table__.begin();itor!=__normal_button_relation_unit_table__.end();itor++)
			if (itor->hwnd == hwnd)
			{
				bg_color = itor->background_color;
				fg_color = itor->foreground_color;
				pushed = itor->pushed;
				break;
			}
		if (GetRValue(bg_color > 127) && GetGValue(bg_color > 127) && GetBValue(bg_color > 127))
			middle_color_r = GetRValue(bg_color) - 20, middle_color_g = GetGValue(bg_color) - 20, middle_color_b = GetBValue(bg_color) - 20;
		else
			middle_color_r = GetRValue(bg_color) + 20, middle_color_g = GetGValue(bg_color) + 20, middle_color_b = GetBValue(bg_color) + 20;
		D2D1_GRADIENT_STOP stops[3];
		if (pushed)
		{
			stops[0].color = D2D1::ColorF(bg_color);
			stops[0].position = 0.5;
			stops[1].color = D2D1::ColorF(RGB(middle_color_r, middle_color_g, middle_color_b));
			stops[1].position = 0.1;
			stops[2].color = D2D1::ColorF(RGB(middle_color_r, middle_color_g, middle_color_b));
			stops[2].position = 1.0;
		}
		else
		{
			stops[0].color = D2D1::ColorF(bg_color);
			stops[0].position = 0.1;
			stops[1].color = D2D1::ColorF(RGB(middle_color_r, middle_color_g, middle_color_b));
			stops[1].position = 0.5;
			stops[2].color = D2D1::ColorF(bg_color);
			stops[2].position = 1.0;
		}
		if (FAILED(iter->device_context_2d->CreateGradientStopCollection(stops, 3, &gradient_stop_collection)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(iter->device_context_2d->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(1, client_rect.top), D2D1::Point2F(1, client_rect.bottom)), gradient_stop_collection.Get(), &linear_gradient_brush)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(iter->device_context_2d->CreateSolidColorBrush(D2D1::ColorF(bg_color), &border_brush)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(iter->device_context_2d->CreateSolidColorBrush(D2D1::ColorF(fg_color), &text_brush)))
		{
			throw PaintControlFailed();
			break;
		}
		iter->device_context_2d->FillRectangle(D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), border_brush.Get());
		iter->device_context_2d->FillRectangle(D2D1::RectF(client_rect.left + 1, client_rect.top + 1, client_rect.right - 1, client_rect.bottom - 1), linear_gradient_brush.Get());
		wchar_t window_text[8192];
		GetWindowText(hwnd, window_text, 8192 - 1);
		iter->device_context_2d->DrawText(window_text, wcslen(window_text), iter->text_format.Get(), D2D1::RectF(client_rect.left, client_rect.top / 2 + 10, client_rect.right, client_rect.bottom / 2 - 10), text_brush.Get());
		if (FAILED(iter->device_context_2d->EndDraw()))
			throw PaintControlFailed();
		if (FAILED(iter->swap_chain->Present(true,false)))
			throw PaintControlFailed();
		break;
	}
	case WM_DESTROY:
	{
		for (list<BasicControlRelationUnit>::iterator itor = __normal_button_relation_unit_table__.begin(); itor != __normal_button_relation_unit_table__.end(); itor++)
		{
			if (itor->hwnd == hwnd)
			{
				break;
			}
		}
		for (list<BasicControlPaintUnit>::iterator itor = __normal_button_paint_unit_table__.begin(); itor != __normal_button_paint_unit_table__.end(); itor++)
		{
			if (itor->hwnd == hwnd)
			{
				ComPtr<ID2D1Effect>effect;
				__normal_button_paint_unit_table__.erase(itor);
				break;
			}
		}
		break;
	}
	case WM_CREATE:
		__normal_button_relation_unit_table__.push_back({ hwnd,RGB(230,230,230),RGB(230,230,230),RGB(0,0,0),false });
		__normal_button_paint_unit_table__.push_back({ 0 });
		__normal_button_paint_unit_table__.back().hwnd = hwnd;
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void UnregisterControls()
{
	UnregisterClass(L"__NORMAL_BUTTON__", ApplicationInstance);
}

void RegisterControls()
{
	WNDCLASS normal_button_class = { 0 };
	normal_button_class.lpfnWndProc = NormalButtonProc;
	normal_button_class.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	normal_button_class.hInstance = ApplicationInstance;
	normal_button_class.hCursor = LoadCursor(ApplicationInstance, IDC_ARROW);
	normal_button_class.lpszClassName = L"__NORMAL_BUTTON__";
	if (RegisterClass(&normal_button_class) == NULL)
	{
		throw RegisterControlsFailed();
		return;
	}
}