
#pragma once
#include <string>
#include "..\Framework\TextSurface.h"
#include "..\Framework\Mouse.h"
#include "..\Framework\Keyboard.h"
#include "GUIElement.h"
#include <time.h>

class GUITextInput :public GUIElement  {
public:
	GUITextInput(std::string name, float x, float y, int width, int height, std::wstring fontfamily);

	void Update(Mouse* _mouse, Keyboard* kbd);
	void Draw(Graphics& gfx);

	void SetMaxChar(int maxchar) { this->maxchar = maxchar; }
	void SetTextColor(Color newcolor) { inputTextColor = newcolor; }
	void SetTypePassword(bool type) { isPassword = type; }
	void SetPlaceHolder(std::string text) { placeholder = text; }
	void SetPlaceHolderColor(Color newcolor) { phcolor = newcolor; }
	std::string GetInput() const { return inputText; }
private:
	void DrawActiveCursor(int x, int y, Graphics& gfx);
	bool Blink();
private:
	bool isPassword;
	Color inputTextColor;
	int maxchar;
	std::string placeholder;
	Color phcolor;
	std::string inputText;
private:
	const float fontsize;
	const TextSurface::Font font;
	const Surface dot;
	time_t last;
	int seccount = 0;
};