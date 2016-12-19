#pragma once#
#include "..\Framework\Rect.h"
#include "..\Framework\Graphics.h"
#include "..\Framework\Mouse.h"
#include "..\Framework\Keyboard.h"
#include "Border.h"
#include <string>

class GUIElement {
public:
	enum eType {
		BUTTON,
		PANEL,
		TEXTINPUT,
		CHECKBOX,
		LIST,
		SLIDER
	};
public:
	GUIElement(std::string name, RectF rect,eType type);
	virtual void Draw(Graphics& gfx);
	virtual void Update(Mouse* _mouse, Keyboard* kbd);
	bool IsHover();
	bool IsLMB();
	void Enable() { Enabled = true; }
	void Disable() { Enabled = false; }

	void SetBorder(bool stt) { eBorder.isOn = stt; }
	void SetBorderColor(Color newcolor) { eBorder.borderColor = newcolor; }
	void SetBorderSize(int newsize) { eBorder.borderSize = newsize; }
	eType GetType() { return type; }
	std::string GetName() const { return Name; }
private:
	void DrawBorder(Graphics& gfx);
private:
	Border eBorder; // element border
	const std::string Name; // name of element
	const eType type;
protected:
	bool Enabled; // enabled or disabled
	bool Active; // is element active
	bool LMB; // is mouse was pressed
	bool Hover; // is mouse over the button
	RectF Box;			// element rect(box)
};