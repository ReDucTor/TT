#include "GUIButton.h"

// NOTE: (reductor) When passing variables by value into a sink (The function will take the argument and store it) it is best to use
// std::move() on these variables (However you should ensure they are only used once), some examples of this are name and title,
// other examples of where this would go wrong is 'path' which is not a sink and gets used multiple times, so should probably be
// 'const std::string &' instead, this removes potential unnecessary copy
GUIButton::GUIButton(std::string name, std::string title, std::string path, float x, float y, std::wstring font, float fontsize ,bool textbold)
	:
	GUIElement(name, { 0,0,0,0 },BUTTON),
	title(title),
	bFont(font,fontsize,textbold),
	Alfa(true),
	fontColor({0,0,0}),
	SelectButton(false),
	Surf{
	Surface::FromFile(path + "_normal.png"),
	Surface::FromFile(path + "_hover.png"),
	Surface::FromFile(path + "_active.png")
}
{
	Box.top = y;
	Box.bottom = y + Surf[0].GetHeight();
	Box.left = x;
	Box.right = x + Surf[0].GetWidth();
	ty = 0;
	tx = 0;
}

void GUIButton::Draw(Graphics & gfx)
{
	if (Enabled) {
		if (SelectButton) {
			if (Active) {
				if (Alfa) {
					gfx.DrawSpriteAlfa((int)Box.left, (int)Box.top, Surf[2]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
				else {
					gfx.DrawSprite((int)Box.left, (int)Box.top, Surf[2]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
			}
			else if (Hover) {
				if (Alfa) {
					gfx.DrawSpriteAlfa((int)Box.left, (int)Box.top, Surf[1]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
				else {
					gfx.DrawSprite((int)Box.left, (int)Box.top, Surf[1]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
			}
			else {
				if (Alfa) {
					gfx.DrawSpriteAlfa((int)Box.left, (int)Box.top, Surf[0]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
				else {
					gfx.DrawSprite((int)Box.left, (int)Box.top, Surf[0]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);

				}
			}
		}
		else {
			if (LMB) {
				if (Alfa) {
					gfx.DrawSpriteAlfa((int)Box.left, (int)Box.top, Surf[2]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
				else {
					gfx.DrawSprite((int)Box.left, (int)Box.top, Surf[2]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
			}
			else if (Hover) {
				if (Alfa) {
					gfx.DrawSpriteAlfa((int)Box.left, (int)Box.top, Surf[1]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
				else {
					gfx.DrawSprite((int)Box.left, (int)Box.top, Surf[1]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
			}
			else {
				if (Alfa) {
					gfx.DrawSpriteAlfa((int)Box.left, (int)Box.top, Surf[0]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);
				}
				else {
					gfx.DrawSprite((int)Box.left, (int)Box.top, Surf[0]);
					gfx.DrawText(title, Box, bFont, fontColor, TextSurface::Alignment::Center);

				}
			}
		}
		

		GUIElement::Draw(gfx);
	}
}

void GUIButton::Update(Mouse * _mouse, Keyboard * kbd)
{
	if (Enabled) {
		GUIElement::Update(_mouse,kbd);
		if (SelectButton) {
			if (LMB) {
				Active = true;
			}
			else if (!Hover && _mouse->LeftIsPressed()) {
				Active = false;
			}
		}
	}
}
