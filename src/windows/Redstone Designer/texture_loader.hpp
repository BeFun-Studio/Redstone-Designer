#pragma once
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include "def.hpp"

using namespace std;
class Texture
{
private:
	unsigned int pixel_count;
	unsigned short width, height;
	unsigned char* red;
	unsigned char* green;
	unsigned char* blue;
	unsigned char* alpha;
public:
	Texture()
	{
	}
	Texture(LPCWSTR load_path)
	{
		FILE* fp;
		if ((fp = _wfopen(load_path, L"rb")) == NULL)
		{
			fclose(fp);
			throw FileNotFound();
		}
		unsigned int current_read_block;
		unsigned char png_head[8];
		const unsigned char correct_png_head[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
		if (fread(png_head, 8, 1, fp) > 1)
		{
			throw FileStructureDamaged();
			return;
		}
		if (png_head != correct_png_head)
		{
			throw FileStructureDamaged();
			return;
		}
		vector<int>pixels;
	}
};