#pragma once
#include "..\Framework\Rect.h"
#include "..\Framework\Colors.h"
#include <string>
#include "Border.h"

class Label {
public:
	Label()
		:
		labelTextColor({ 0,0,0 }),
		labelText(""),
		labelBgColor(Colors::Gray),
		isOn(false)
	{}
	Border labelBorder;
	Color labelTextColor;
	bool isOn;
	std::string labelText;
	Color labelBgColor;
	RectF labelBox;
};