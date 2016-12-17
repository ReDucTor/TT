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
