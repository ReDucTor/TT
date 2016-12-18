#include "GUIButton.h"

GUIButton::GUIButton(std::string name, std::string title, std::string path, float x, float y, int width, int height, std::wstring font, float fontsize ,bool textbold)
	:
	GUIElement(name, { y, y + height, x, x + width }),
	title(title),
	bFont(font,fontsize,textbold)
{
	std::string pth[3] = { "_normal","_hover","_active" };
	for(int i = 0; i < 3;i++){
		std::string fullpath = path + pth[i] + ".png";
		Surf[i] = Surface::FromFile(fullpath);
	}
}
