#pragma once#
#include "..\Framework\Rect.h"
#include "..\Framework\Graphics.h"
#include "..\Framework\Mouse.h"
#include "..\Framework\Keyboard.h"
#include "Border.h"
#include "Label.h"

#include <string>

class GUIElement {
protected:
	enum State {
		ACTIVE,
		HOVER,
		NORMAL
	};
public:
	GUIElement(std::string name, RectF rect);
	virtual void Draw(Graphics& gfx) {}
	virtual void Update(Mouse* _mouse,Keyboard* kbd) {}
	virtual bool IsHover(Mouse* _mouse);
	virtual bool IsLMB(Mouse* _mouse);
	std::string GetName() { return Name; }
private:
	void DrawBorder(Graphics& gfx);
protected:
	Border eBorder;
	Label eLabel;
protected:
	State Status;	//Element state
	const std::string Name; // name of element
	RectF Box;			// element rect(box)
};