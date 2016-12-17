#include "GUIElement.h"

GUIElement::GUIElement(std::string name, RectF rect)
	:
	Name(name),
	Box(rect),
	Status(NORMAL)
{
}

bool GUIElement::IsHover(Mouse * _mouse)
{
	if (Box.Overlaps(_mouse->GetPosX(), _mouse->GetPosY()))
		return true;
	return false;
}

bool GUIElement::IsLMB(Mouse * _mouse)
{
	if (IsHover(_mouse) && _mouse->LeftIsPressed())
		return true;
	return false;
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
