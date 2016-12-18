#pragma once
#include "GUIElement.h"

class GUIButton :public GUIElement {
public:
	GUIButton(std::string name, std::string title, std::string path,float x, float y,int width,int height,std::wstring font,float fontsize,bool textbold);
private:
	std::string title; // Button text 
	TextSurface::Font bFont; // button font
	Surface Surf[3]; // 0 = normal 1 = hover 2 = active
};