#include "GUIElement.h"

GUIElement::GUIElement(std::string name, RectF rect,eType type)
	:
	Name(name),
	Box(rect),
	Active(false),
	LMB(false),
	Hover(false),
	Enabled(true),
	type(type)
{
}

void GUIElement::Draw(Graphics & gfx)
{
	DrawBorder(gfx);
}

// NOTE: (reductor) As '_mouse' and 'kdb' are required should use references
// instead, also might be worth using 'const' if possible. 'kdb' also seemed
// unused currently.
void GUIElement::Update(Mouse * _mouse, Keyboard * kbd)
{
	if (Box.Overlaps((float)_mouse->GetPosX(), (float)_mouse->GetPosY())) {
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

// NOTE: (reductor) This should be a const method
bool GUIElement::IsHover()
{
	return Hover;
}

// NOTE: (reductor) This should be a const method
bool GUIElement::IsLMB()
{
	return LMB;
}

void GUIElement::DrawBorder(Graphics& gfx)
{
	if (eBorder.isOn) {
		for (int s = 0; s < eBorder.borderSize; s++) {
			for (int i = (int)Box.left; i < Box.right; i++) {
				gfx.PutPixel(i + 1, (int)Box.top+s, { 0,0,0 });
			}
			for (int i = (int)Box.left; i < Box.right; i++) {
				gfx.PutPixel(i, (int)Box.bottom-s, { 0,0,0 });
			}
			for (int i = (int)Box.top; i < Box.bottom; i++) {
				gfx.PutPixel((int)Box.left-s, i, { 0,0,0 });
			}
			for (int i = (int)Box.top; i < Box.bottom; i++) {
				gfx.PutPixel((int)Box.right+s, i + 1, { 0,0,0 });
			}
		}
	}
}
