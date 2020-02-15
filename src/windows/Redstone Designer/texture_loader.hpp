#pragma once
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "def.hpp"
#include "api.hpp"

using namespace std;
struct Texture
{
	unsigned char reds;
	unsigned char greens;
	unsigned char blues;
	unsigned char alphas;
	unsigned int height;
	unsigned int width;
};
bool LoadTexture(LPCWSTR texture_path)
{
	
}