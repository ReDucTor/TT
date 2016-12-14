#include "BMP.h"

void LoadBMP(const std::string fn, std::vector<Color>& image, unsigned int &width, unsigned int &height)
{
	std::ifstream fin(fn.c_str(), std::ios::binary);
		char signature[2];
		fin.read(signature, sizeof(signature));
		if (signature[0] == 'B' && signature[1] == 'M') {
			BMPFileHeader fileheader;
			BMPInfoHeader infoheader;
			fin.read((char*)&fileheader, sizeof(fileheader));
			fin.read((char*)&infoheader, sizeof(infoheader));

			width = infoheader.width;
			height = infoheader.height;

			fin.seekg(fileheader.offset, fin.beg);
			int PaddingBytesPerRow = (4 - ((infoheader.width * 3) % 4)) % 4;
			Pixels pxl;
			int cc = 0;
			image.resize(infoheader.width*infoheader.height);
			for (unsigned int y = 0; y < infoheader.height; y++) {
				for (unsigned int x = 0; x < infoheader.width; x++) {
					fin.read((char*)&pxl, sizeof(pxl));
					cc = x + ((infoheader.height - 1) - y) * infoheader.width;
					image[cc].SetR(pxl.r);
					image[cc].SetG(pxl.g);
					image[cc].SetB(pxl.b);
				}
				fin.seekg(PaddingBytesPerRow, fin.cur);
			}
		}
		fin.close();

}