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

list<BasicControlRelationUnit> __normal_button_relation_unit_table__;

LRESULT CALLBACK NormalButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		UpdateWindow(hwnd);
		break;
	case WM_MOUSEHOVER:
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 0;
		tme.hwndTrack = hwnd;
		TrackMouseEvent(&tme);
		for (list<BasicControlRelationUnit>::iterator itor = __normal_button_relation_unit_table__.begin(); itor != __normal_button_relation_unit_table__.end(); itor++)
			if (itor->hwnd == hwnd)
			{
				unsigned char current_r = GetRValue(itor->background_color);
				unsigned char current_g = GetGValue(itor->background_color);
				unsigned char current_b = GetBValue(itor->background_color);
				if (current_r + 50 >= 255)
					current_r = 255;
				else
					current_r += 255;
				if (current_g + 50 >= 255)
					current_g = 255;
				else
					current_g = 255;
				if (current_b + 50 >= 255)
					current_b = 255;
				else
					current_b += 255;
				itor->background_color = RGB(current_r, current_g, current_b);
				RECT client_rect;
				GetClientRect(hwnd, &client_rect);
				InvalidateRect(hwnd, &client_rect, false);
			}
		break;
	}
	case WM_MOUSELEAVE:
	{
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
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		ComPtr<ID2D1Factory>factory;
		ComPtr<ID2D1HwndRenderTarget>render_target;
		ComPtr<ID2D1GradientStopCollection>gradient_stop_collection;
		ComPtr<ID2D1SolidColorBrush>border_brush;
		ComPtr<ID2D1LinearGradientBrush>linear_gradient_brush;
		ComPtr<ID2D1SolidColorBrush>text_brush;
		ComPtr<IDWriteFactory>write_factory;
		ComPtr<IDWriteTextFormat>text_format;
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &factory)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(client_rect.right - client_rect.left, client_rect.bottom - client_rect.top)), &render_target)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), &write_factory)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(write_factory->CreateTextFormat(L"Unifont", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"", &text_format)))
		{
			throw PaintControlFailed();
			break;
		}
		text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		render_target->BeginDraw();
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
		if (GetRValue(bg_color > 127) || GetGValue(bg_color > 127) || GetBValue(bg_color > 127))
			middle_color_r = bg_color - 20, middle_color_g = bg_color - 20, middle_color_b = bg_color - 20;
		else
			middle_color_r = bg_color + 20, middle_color_g = bg_color + 20, middle_color_b = bg_color + 20;
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
		if (FAILED(render_target->CreateGradientStopCollection(stops, 3, &gradient_stop_collection)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(render_target->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(1, client_rect.top), D2D1::Point2F(1, client_rect.bottom)), gradient_stop_collection.Get(), &linear_gradient_brush)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(bg_color), &border_brush)))
		{
			throw PaintControlFailed();
			break;
		}
		if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(fg_color), &text_brush)))
		{
			throw PaintControlFailed();
			break;
		}
		render_target->FillRectangle(D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), border_brush.Get());
		render_target->FillRectangle(D2D1::RectF(client_rect.left + 1, client_rect.top + 1, client_rect.right - 1, client_rect.bottom - 1), linear_gradient_brush.Get());
		wchar_t window_text[8192];
		GetWindowText(hwnd, window_text, 8192 - 1);
		render_target->DrawText(window_text, wcslen(window_text), text_format.Get(), D2D1::RectF(client_rect.left, client_rect.top, client_rect.right, client_rect.bottom), text_brush.Get());
		if (FAILED(render_target->EndDraw()))
			throw PaintControlFailed();
		break;
	}
	case WM_DESTROY:
	{
		for (list<BasicControlRelationUnit>::iterator itor = __normal_button_relation_unit_table__.begin(); itor != __normal_button_relation_unit_table__.end(); itor++)
		{
			if (itor->hwnd == hwnd)
			{
				__normal_button_relation_unit_table__.erase(itor);
				break;
			}
		}
		break;
	}
	case WM_CREATE:
		__normal_button_relation_unit_table__.push_back({ hwnd,RGB(200,200,200),RGB(200,200,200),RGB(0,0,0),false });
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