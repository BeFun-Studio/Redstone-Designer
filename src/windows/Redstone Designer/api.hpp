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

struct BeepCommand
{
    bool beep;
    DWORD frequency;
    DWORD duration;
};

class BeepFrequencySequence
{
private:
    std::vector<BeepCommand>beep_commands;
    size_t current_command_index;
public:
    BeepFrequencySequence()
    {
        this->current_command_index = 0;
    }
    BeepFrequencySequence(size_t argument_count, ...)
    {
        va_list args;
        va_start(args, argument_count);
        for (int i = 0; i < argument_count; i++)
            this->beep_commands.push_back(va_arg(args, BeepCommand));
        va_end(args);
        this->current_command_index = 0;
    }
    bool LoadFromFile(LPCWSTR filename)
    {
        FILE* fp = _wfopen(filename, L"r");
        if (fp == NULL)
        {
            fclose(fp);
            return false;
        }
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) % 9 != 0)
        {
            fclose(fp);
            return false;
        }
        bool beep;
        DWORD frequency;
        DWORD duration;
        for (int i = 0; i < ftell(fp) / 5; i++)
        {
            fread(&beep, 1, 1, fp);
            fread(&frequency, sizeof(int), 1, fp);
            fread(&beep, sizeof(int), 1, fp);
            BeepCommand push_command = { beep,frequency,duration };
            this->beep_commands.push_back(push_command);
        }
        fclose(fp);
        return true;
    }
    void Load(size_t argument_count, ...)
    {
        va_list args;
        va_start(args, argument_count);
        for (int i = 0; i < argument_count; i++)
            this->beep_commands.push_back(va_arg(args, BeepCommand));
        va_end(args);
        this->current_command_index = 0;
    }
    bool Play()
    {
        if (this->current_command_index == this->beep_commands.size() - 1)
            return false;
        if (!this->beep_commands[this->current_command_index].beep)
        {
            Sleep(this->beep_commands[this->current_command_index].duration);
            return true;
        }
        Beep(this->beep_commands[this->current_command_index].frequency, this->beep_commands[this->current_command_index].duration);
        return true;
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