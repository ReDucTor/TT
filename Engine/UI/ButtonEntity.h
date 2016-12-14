#pragma once
#include "..\\Framework\Surface.h"

class ButtonEntity {
public:
	ButtonEntity(int x, int y ,int width ,int height,TransparentSurface * texture)
		:
		x(x),
		y(y),
		width(width),
		height(height),
		texture(texture)
	{}
protected:
	TransparentSurface* texture;
	const int x, y, width, height;
};