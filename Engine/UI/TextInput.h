
#pragma once
#include <string>
#include "..\Framework\Rect.h"
#include "..\Framework\TextSurface.h"
#include "..\Framework\Mouse.h"
#include "..\Framework\Keyboard.h"
#include "..\Framework\Graphics.h"
#include <time.h>

class TextInput {
public:
	TextInput(float x, float y, int width, int height, std::wstring fontfamily = L"Minion Pro")
		:
		Active(false),
		font(fontfamily, fontsize, false),
		box(y, y + height, x, x + width),
		text(""),
		fontsize((((float)height) / 3.5) * 2),
		maxchar(20),
		isPassword(true),
		dot(Surface::FromFile("..\\data\\textures\\dot.png")),
		textcolor({ 0,0,0 }),
		phcolor({ 50,50,50 }),
		placeholder("")
	{
	}
	void Update(Mouse& _mouse, Keyboard& kbd);
	void Draw(Graphics& gfx);

	void SetMaxChar(int maxchar) { this->maxchar = maxchar; }
	void SetTextColor(Color newcolor) { textcolor = newcolor; }
	void SetTypePassword(bool type) { isPassword = type; }
	void SetPlaceHolder(std::string text) { placeholder = text; }
	void SetPlaceHolderColor(Color newcolor) { phcolor = newcolor; }
	std::string GetInput() const { return text; }
private:
	void DrawActiveCursor(int x, int y, Graphics& gfx);
	bool Blink();
private:
	bool isPassword;
	Color textcolor;
	int maxchar;
	std::string placeholder;
	Color phcolor;
private:
	bool Active;
	std::string text;
	const float fontsize;
	const TextSurface::Font font;
	RectF box;
	const Surface dot;
	time_t last;
	int seccount = 0;
};