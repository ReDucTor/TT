#pragma once#
#include "..\Framework\Rect.h"
#include "..\Framework\Graphics.h"
#include "..\Framework\Mouse.h"
#include "..\Framework\Keyboard.h"
#include "Border.h"
#include "Label.h"

#include <string>

class GUIElement {
public:
	GUIElement(std::string name, RectF rect);
	virtual void Draw(Graphics& gfx);
	virtual void Update(Mouse* _mouse, Keyboard* kbd);
	bool IsHover();
	bool IsLMB();

	void SetBorder(bool stt) { eBorder.isOn = stt; }
	void SetBorderColor(Color newcolor) { eBorder.borderColor = newcolor; }
	void SetBorderSize(int newsize) { eBorder.borderSize = newsize; }

	std::string GetName() const { return Name; }
private:
	void DrawBorder(Graphics& gfx);
private:
	Border eBorder; // element border
	const std::string Name; // name of element
protected:
	bool Active;
	bool LMB;
	bool Hover;
	RectF Box;			// element rect(box)
};