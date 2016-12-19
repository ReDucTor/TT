#pragma once
#include "GUIElement.h"

class GUIPanel :public GUIElement {
public:
	GUIPanel(std::string name ,std::string path,float x , float y);
	void Draw(Graphics& gfx);
	void DrawAlfa(bool yn) { Alfa = yn; }
private:
	bool Alfa;
	Surface surf;
};