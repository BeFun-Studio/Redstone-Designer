#pragma once
#include <Windows.h>
#include <stdarg.h>
#include <d2d1.h>

#ifndef DLLAPI
#ifdef DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#endif

typedef enum
{
	TOP=0,
	BOTTOM,
	LEFT,
	RIGHT
}DRAW_DIRECTIONS;

#ifdef __cplusplus
extern "C"{
#endif

DLLAPI bool FillGradientRect(HWND hwnd, RECT draw_rect, DRAW_DIRECTIONS draw_direction, ID2D1HwndRenderTarget* render_target, COLORREF start_color, COLORREF end_color);

#ifdef __cplusplus
}
#endif