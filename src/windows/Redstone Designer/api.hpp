#pragma once
#ifndef PRIVATE_API_HPP
#define PRIVATE_API_HPP
#include <Windows.h>
#include <stdarg.h>
#include <thread>

#define RELEASE_DIRECTX_RESOURCE(PTR) if(PTR){PTR->Release();PTR=NULL;}
#define LODWORD(l) ((DWORD)(((DWORD_PTR)(l)) & 0xffffffff))
#define HIDWORD(l) ((DWORD)((((DWORD_PTR)(l)) >> 32) & 0xffffffff))
#define CPU_THREAD_COUNT GetCpuThreadCount()

template<class type>class DirectXResource
{
private:
    type resource; 
public:
    DirectXResource()
    {
        this->resource = NULL;
    }
    DirectXResource(type res)
    {
        this->resource = res;
    }
    type GetResource()
    {
        return this->resource;
    }
    type* GetResourcePointer()
    {
        return &(this->resource);
    }
    void Release()
    {
        RELEASE_DIRECTX_RESOURCE(this->resource);
    }
    ~DirectXResource()
    {
        this->Release();
    }
};

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
unsigned int AllocateTasksToCpuCores(unsigned int task_count, ...)
{
    va_list args;
    va_start(args, task_count);
    HANDLE current_task_handle;
    unsigned int allocated_task_count=0;
    unsigned int current_cpu_id = 1;
    for (int i = 0; i < task_count; i++)
    {
        current_task_handle = va_arg(args, HANDLE);
        if (current_cpu_id == CPU_THREAD_COUNT)
            current_cpu_id = 0x00000001;
        allocated_task_count++;
        if (SetThreadAffinityMask(current_task_handle, current_cpu_id) == NULL)
            return allocated_task_count;
    }
    va_end(args);
    return 0;
}

#endif