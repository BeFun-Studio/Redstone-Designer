#pragma once
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <d2d1.h>
#include <d3d10.h>
#include "def.hpp"
#include "api.hpp"
using namespace std;

typedef struct
{
	D2D1::ColorF *pixels;
	unsigned int height;
	unsigned int width;
}Texture;

bool LoadTexture(LPCWSTR texture_path, Texture* dest)
{
	
}