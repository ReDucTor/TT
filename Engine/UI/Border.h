#pragma once
#include "..\Framework\Colors.h"

class Border {
public:
	Border()
		:
		borderColor({0,0,0}),
		borderSize(1),
		isOn(false)
	{}
	Color borderColor;
	int borderSize;
	bool isOn;
};