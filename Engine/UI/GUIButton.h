#pragma once
#include "GUIElement.h"

class GUIButton :public GUIElement {
public:
	GUIButton(std::string name, std::string title, std::string path,float x, float y,int width,int height,std::wstring font,float fontsize,bool textbold);
	void Draw(Graphics& gfx);
	void Update(Mouse* _mouse, Keyboard* kbd);

	void DrawAsAlfa(bool yn) { Alfa = yn; }
	void SetTitle(std::string newttl) { title = newttl; }
	void SetTitleColor(Color newcolor) { fontColor = newcolor; }
	void SetTitlePosition(float x, float y) { tx = x; ty = y; }
private:
	bool Alfa; // draw alfa or normal
	float tx, ty;
	std::string title; // Button text 
	Color fontColor;
	TextSurface::Font bFont; // button font
	Surface Surf[3]; // 0 = normal 1 = hover 2 = active
};