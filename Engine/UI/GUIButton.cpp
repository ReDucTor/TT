#include "GUIButton.h"

GUIButton::GUIButton(std::string name, std::string title, std::string path, float x, float y, int width, int height, std::wstring font, float fontsize ,bool textbold)
	:
	GUIElement(name, { y, y + height, x, x + width }),
	title(title),
	bFont(font,fontsize,textbold),
	Alfa(true),
	fontColor({0,0,0}),
	Surf{
	Surface::FromFile(path + "_normal.png"),
	Surface::FromFile(path + "_hover.png"),
	Surface::FromFile(path + "_active.png")
}
{
	ty = y + (height /2)- fontsize;
	tx = x + (width/2) - (fontsize*title.size()/2);
}

void GUIButton::Draw(Graphics & gfx)
{
	if (Enabled) {
		if (LMB) {
			if (Alfa) {
				gfx.DrawSpriteAlfa(Box.left, Box.top, Surf[2]);
				gfx.DrawText(title, Box, bFont, fontColor,TextSurface::Alignment::Center);
			}
			else {
				gfx.DrawSprite(Box.left, Box.top, Surf[2]);
				gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
			}
		}
		else if (Hover) {
			if (Alfa) {
				gfx.DrawSpriteAlfa(Box.left, Box.top, Surf[1]);
				gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
			}
			else {
				gfx.DrawSprite(Box.left, Box.top, Surf[1]);
				gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
			}
		}
		else {
			if (Alfa) {
				gfx.DrawSpriteAlfa(Box.left, Box.top, Surf[0]);
				gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
			}
			else {
				gfx.DrawSprite(Box.left, Box.top, Surf[0]);
				gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				
			}
		}
		GUIElement::Draw(gfx);
	}
}

void GUIButton::Update(Mouse * _mouse, Keyboard * kbd)
{
	if (Enabled) {
		GUIElement::Update(_mouse,kbd);
	}
}
