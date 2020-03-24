#pragma once
#ifndef PRIVATE_API_HPP
#define PRIVATE_API_HPP
#include <Windows.h>
#include <stdarg.h>
#include <thread>

#define RELEASE_COM_RESOURCE(PTR) if(PTR){PTR->Release();PTR=NULL;}
#define CPU_THREAD_COUNT GetCpuThreadCount()

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

unsigned int GetCpuThreadCount()
{
    return std::thread::hardware_concurrency();
}

void AllocateTaskToCpuCore(unsigned int cpu_core_id, HANDLE thread_handle)
{
    if (cpu_core_id == 0)
    {
        cpu_core_id = 1;
        SetThreadAffinityMask(thread_handle, cpu_core_id);
    }
    else
    {
        for (volatile int i = 0, j = cpu_core_id; i < j; i++)
            cpu_core_id *= 2;
        SetThreadAffinityMask(thread_handle, cpu_core_id);
    }
}

#endif