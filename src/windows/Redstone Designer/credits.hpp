#pragma once
#include <Windows.h>

#define ONE_

HWND CreditsWindowHandle;

HANDLE PlayBgmThread;
HANDLE UpdateCreditsWindowThread;

unsigned int CurrentFrame = 0;

DWORD WINAPI PlayBgmThreadProc(DWORD lpParameter)
{
	while(true)
		PlaySound(L"media\\Clouds.wav", NULL, SND_SYNC);
	return 0;
}

DWORD WINAPI UpdateCreditsWindowThreadProc(DWORD lpParameter)
{
	while (true)
	{
		RECT client_rect;
		GetClientRect(CreditsWindowHandle, &client_rect);
		InvalidateRect(CreditsWindowHandle, &client_rect, false);
		Sleep(16);
	}
}

LRESULT CreditsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		FillRect(hdc, &client_rect, CreateSolidBrush(RGB(178, 34, 34)));
		if (CurrentFrame < 360)
			break;
		switch (CurrentFrame)
		{
		case 721:
			break;
		}
		CurrentFrame++;
		break;
	}
	case WM_CREATE:
		break;
	}
}