#include "TextureImporter.h"



BMPData TextureImporter::LoadBMP(const char * BMPname)
{
	unsigned char header[54];
	BMPData bmph;
	FILE * file;
	fopen_s(&file, BMPname, "rb");

	if (RightBMPFormat(header, file))
	{
		bmph.position = *(int*)&(header[0x0A]);
		bmph.imageSize = *(int*)&(header[0x22]);
		bmph.width = *(int*)&(header[0x12]);
		bmph.height = *(int*)&(header[0x16]);

	}

	if (bmph.imageSize == 0)   
		bmph.imageSize = bmph.width * bmph.height * 3;
	if (bmph.position == 0)      
		bmph.position = 54;

	bmph.data = new unsigned char[bmph.imageSize];

	fseek(file, bmph.position, 0);
	fread(bmph.data, 1, bmph.imageSize, file);
	fclose(file);

	return bmph;

}

bool TextureImporter::RightBMPFormat(unsigned char  BMPheader[], FILE * BMPfile)
{
	if (!BMPfile)
	{
		printf("Image could not be opened\n");
		return 0;
	}

	if (fread(BMPheader, 1, 54, BMPfile) != 54)
	{
		printf("Not a correct BMP file\n");
		return false;
	}

	if (BMPheader[0] != 'B' || BMPheader[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}


}
