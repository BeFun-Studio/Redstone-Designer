// dllmain.cpp : 定义 DLL 应用程序的入口点。
#define DLL

#include "ui_extension.h"

DLLAPI bool FillGradientRect(HWND hwnd, RECT draw_rect, DRAW_DIRECTIONS draw_direction, ID2D1HwndRenderTarget* render_target, COLORREF start_color, COLORREF end_color)
{
    int color_change_distance_g;
    int color_change_distance_r;
    int color_change_distance_b;
    bool direction_r = false;
    bool direction_g = false;
    bool direction_b = false;
    color_change_distance_r = abs(GetRValue(start_color) - GetRValue(end_color));
    color_change_distance_g = abs(GetGValue(start_color) - GetGValue(end_color));
    color_change_distance_b = abs(GetBValue(start_color) - GetBValue(end_color));
    if (GetRValue(start_color) < GetRValue(end_color))
        direction_r = true;
    if (GetGValue(start_color) < GetGValue(end_color))
        direction_g = true;
    if (GetBValue(start_color) < GetBValue(end_color))
        direction_b = true;
    switch (draw_direction)
    {
    case TOP:
        color_change_distance_r /= (draw_rect.bottom - draw_rect.top);
        color_change_distance_g /= (draw_rect.bottom - draw_rect.top);
        color_change_distance_b /= (draw_rect.bottom - draw_rect.top);
        break;
    case BOTTOM:
        color_change_distance_r /= (draw_rect.bottom - draw_rect.top);
        color_change_distance_g /= (draw_rect.bottom - draw_rect.top);
        color_change_distance_b /= (draw_rect.bottom - draw_rect.top);
        break;
    case LEFT:
        color_change_distance_r /= (draw_rect.right - draw_rect.left);
        color_change_distance_g /= (draw_rect.right - draw_rect.left);
        color_change_distance_b /= (draw_rect.right - draw_rect.left);
        break;
    case RIGHT:
        color_change_distance_r /= (draw_rect.right - draw_rect.left);
        color_change_distance_g /= (draw_rect.right - draw_rect.left);
        color_change_distance_b /= (draw_rect.right - draw_rect.left);
        break;
    }
    unsigned int filled_distance = 0;
    unsigned char current_r = GetRValue(start_color);
    unsigned char current_g = GetGValue(start_color);
    unsigned char current_b = GetBValue(start_color);
    switch (draw_direction)
    {
    case TOP:
        while (filled_distance < (draw_rect.bottom - draw_rect.top))
        {
            RECT fill_rect = draw_rect;
            fill_rect.bottom = draw_rect.bottom - filled_distance;
            fill_rect.top -= fill_rect.bottom - 1;
            ID2D1SolidColorBrush* brush;
            if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(RGB(current_r, current_g, current_b), 1.0f), &brush)))
                return false;
            render_target->FillRectangle(D2D1::Rect(fill_rect.left, fill_rect.top, fill_rect.right, fill_rect.bottom), brush);
            brush->Release();
            filled_distance++;
            if (filled_distance % color_change_distance_r == 0)
                if (direction_r)
                    current_r++;
                else
                    current_r--;
            if (filled_distance % color_change_distance_g == 0)
                if (direction_g)
                    current_g++;
                else
                    current_g--;
            if (filled_distance % color_change_distance_b == 0)
                if (direction_b)
                    current_b++;
                else
                    current_b--;
        }
        break;
    case BOTTOM:
        while (filled_distance < (draw_rect.bottom - draw_rect.top))
        {
            RECT fill_rect = draw_rect;
            fill_rect.bottom = draw_rect.top + filled_distance;
            fill_rect.top = fill_rect.bottom - 1;
            ID2D1SolidColorBrush* brush;
            if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(RGB(current_r, current_g, current_b), 1.0f), &brush)))
                return false;
            render_target->FillRectangle(D2D1::Rect(fill_rect.left, fill_rect.top, fill_rect.right, fill_rect.bottom), brush);
            brush->Release();
            filled_distance++;
            if (filled_distance % color_change_distance_r == 0)
                if (direction_r)
                    current_r++;
                else
                    current_r--;
            if (filled_distance % color_change_distance_g == 0)
                if (direction_g)
                    current_g++;
                else
                    current_g--;
            if (filled_distance % color_change_distance_b == 0)
                if (direction_b)
                    current_b++;
                else
                    current_b--;
        }
        break;
    case LEFT:
        while (filled_distance < (draw_rect.right - draw_rect.left))
        {
            RECT fill_rect = draw_rect;
            fill_rect.right = draw_rect.right - filled_distance;
            fill_rect.left = fill_rect.right - 1;
            ID2D1SolidColorBrush* brush;
            if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(RGB(current_r, current_g, current_b), 1.0f), &brush)))
                return false;
            render_target->FillRectangle(D2D1::Rect(fill_rect.left, fill_rect.top, fill_rect.right, fill_rect.bottom), brush);
            brush->Release();
            filled_distance++;
            if (filled_distance % color_change_distance_r == 0)
                if (direction_r)
                    current_r++;
                else
                    current_r--;
            if (filled_distance % color_change_distance_g == 0)
                if (direction_g)
                    current_g++;
                else
                    current_g--;
            if (filled_distance % color_change_distance_b == 0)
                if (direction_b)
                    current_b++;
                else
                    current_b--;
        }
        break;
    case RIGHT:
        while (filled_distance < (draw_rect.right - draw_rect.left))
        {
            RECT fill_rect = draw_rect;
            fill_rect.right = draw_rect.left + filled_distance;
            fill_rect.left = fill_rect.right - 1;
            ID2D1SolidColorBrush* brush;
            if (FAILED(render_target->CreateSolidColorBrush(D2D1::ColorF(RGB(current_r, current_g, current_b), 1.0f), &brush)))
                return false;
            render_target->FillRectangle(D2D1::Rect(fill_rect.left, fill_rect.top, fill_rect.right, fill_rect.bottom), brush);
            brush->Release();
            filled_distance++;
            if (filled_distance % color_change_distance_r == 0)
                if (direction_r)
                    current_r++;
                else
                    current_r--;
            if (filled_distance % color_change_distance_g == 0)
                if (direction_g)
                    current_g++;
                else
                    current_g--;
            if (filled_distance % color_change_distance_b == 0)
                if (direction_b)
                    current_b++;
                else
                    current_b--;
        }
        break;
    }
    return true;
}

INT APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
