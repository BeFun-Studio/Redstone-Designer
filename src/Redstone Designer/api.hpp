#pragma once
#ifndef PRIVATE_API_HPP
#define PRIVATE_API_HPP
#include <Windows.h>

LOGFONTW CurrentFont;
HFONT font;

void SetFont(HDC hdc, UINT font_size, LPCWSTR font_name,bool italic,bool underline,bool strike_out)
{
    DeleteObject(font);
    CurrentFont.lfCharSet = DEFAULT_CHARSET;
    CurrentFont.lfItalic = italic;
    CurrentFont.lfHeight = font_size;
    CurrentFont.lfWidth = font_size / 2;
    CurrentFont.lfEscapement = 0;
    CurrentFont.lfWeight = FW_NORMAL;
    CurrentFont.lfUnderline = underline;
    CurrentFont.lfStrikeOut = strike_out;
    CurrentFont.lfQuality = PROOF_QUALITY;
    lstrcpyW(CurrentFont.lfFaceName, font_name);
    CurrentFont.lfPitchAndFamily = FF_DONTCARE;
    CurrentFont.lfClipPrecision = CLIP_CHARACTER_PRECIS;
    CurrentFont.lfOutPrecision = OUT_CHARACTER_PRECIS;
    font = CreateFontIndirectW(&CurrentFont);
    SelectObject(hdc, font);
}
HFONT _CreateFont(UINT font_size, LPCWSTR font_name, bool italic, bool underline, bool strike_out)
{
    LOGFONT CurrentFont;
    HFONT font;
    CurrentFont.lfCharSet = DEFAULT_CHARSET;
    CurrentFont.lfItalic = italic;
    CurrentFont.lfHeight = font_size;
    CurrentFont.lfWidth = font_size / 2;
    CurrentFont.lfEscapement = 0;
    CurrentFont.lfWeight = FW_NORMAL;
    CurrentFont.lfUnderline = underline;
    CurrentFont.lfStrikeOut = strike_out;
    CurrentFont.lfQuality = PROOF_QUALITY;
    lstrcpyW(CurrentFont.lfFaceName, font_name);
    CurrentFont.lfPitchAndFamily = FF_DONTCARE;
    CurrentFont.lfClipPrecision = CLIP_CHARACTER_PRECIS;
    CurrentFont.lfOutPrecision = OUT_CHARACTER_PRECIS;
    font = CreateFontIndirectW(&CurrentFont);
    return font;
}
void DeleteFont(void)
{
    DeleteObject(font);
}
void FontOut(HDC hdc, UINT x, UINT y, UINT font_size, LPCWSTR font_name, LPCWSTR output_str,bool italic,bool underline,bool strike_out)
{
    SetFont(hdc, font_size, font_name,italic,underline,strike_out);
    TextOutW(hdc, x, y, output_str, wcslen(output_str));
    DeleteFont();
}
void ShadowOut(HDC hdc, UINT x, UINT y, UINT font_size, LPCWSTR font_name,LPCWSTR output_str, bool italic, bool underline, bool strike_out)
{
    COLORREF original_color = GetTextColor(hdc);
    SetTextColor(hdc, RGB(0, 0, 0));
    FontOut(hdc, x + 3, y + 3, font_size, font_name, output_str, italic, underline, strike_out);
    SetTextColor(hdc, original_color);
    FontOut(hdc, x, y, font_size, font_name, output_str, italic, underline, strike_out);
}
#endif