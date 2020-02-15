#pragma once
#ifndef PRIVATE_API_HPP
#define PRIVATE_API_HPP
#include <Windows.h>

#define RELEASE_D2D_RESOURCE(PTR) if(PTR){PTR->Release();PTR=NULL;}
#define LODWORD(l) ((DWORD)(((DWORD_PTR)(l)) & 0xffffffff))
#define HIDWORD(l) ((DWORD)((((DWORD_PTR)(l)) >> 32) & 0xffffffff))

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
#endif