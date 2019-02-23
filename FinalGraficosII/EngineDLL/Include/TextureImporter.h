#pragma once
#include "Exports.h"

#include <stdio.h>
#include <stdlib.h>


struct BMPData
{
	unsigned int position;
	unsigned int height;
	unsigned int width;
	unsigned int imageSize;
	unsigned char  * data;
};

static class ENGINEDLL_API TextureImporter
{

public:

	static BMPData LoadBMP(const char* BMPname);
	static bool RightBMPFormat(unsigned char  BMPheader[], FILE * BMPfile);
};

