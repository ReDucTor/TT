#pragma once

#include <string>
#include <fstream>
#include <vector>
//#include "Graphics.h"
#include "Colors.h"

struct BMPFileHeader
{
	unsigned int size;
	unsigned short reserved1, reserved2;
	unsigned int offset;
};

struct BMPInfoHeader
{
	unsigned int HeaderSize;
	unsigned int width, height;
	unsigned short planes;
	unsigned short bits;
	unsigned int compression;
	unsigned int imagesize;
	int xResolution, yResolution;
	unsigned int nColors;
	unsigned int importantColors;
};

struct Pixels {
	unsigned char b, g, r;
};

void LoadBMP(const std::string fn,std::vector<Color>& image, unsigned int &width,unsigned int &height);