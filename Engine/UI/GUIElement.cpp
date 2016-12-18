#include "GUIElement.h"

GUIElement::GUIElement(std::string name, RectF rect)
	:
	Name(name),
	Box(rect),
	Active(false),
	LMB(false),
	Hover(false),
	ElementStatus(true)
{
}

void GUIElement::Draw(Graphics & gfx)
{
	DrawBorder(gfx);
}

void GUIElement::Update(Mouse * _mouse, Keyboard * kbd)
{
	if (Box.Overlaps(_mouse->GetPosX(), _mouse->GetPosY())) {
		Hover = true;
	}
	else {
		Hover = false;
	}

	if (Hover && _mouse->LeftIsPressed()) {
		LMB = true;
	}
	else {
		LMB = false;
	}
}

bool GUIElement::IsHover()
{
	return Hover;
}

bool GUIElement::IsLMB()
{
	return LMB;
}

void GUIElement::DrawBorder(Graphics& gfx)
{
	if (eBorder.isOn) {
		for (int s = 0; s < eBorder.borderSize; s++) {
			for (int i = Box.left; i < Box.right; i++) {
				gfx.PutPixel(i + 1, Box.top+s, { 0,0,0 });
			}
			for (int i = Box.left; i < Box.right; i++) {
				gfx.PutPixel(i, Box.bottom-s, { 0,0,0 });
			}
			for (int i = Box.top; i < Box.bottom; i++) {
				gfx.PutPixel(Box.left-s, i, { 0,0,0 });
			}
			for (int i = Box.top; i < Box.bottom; i++) {
				gfx.PutPixel(Box.right+s, i + 1, { 0,0,0 });
			}
		}
	}
}
