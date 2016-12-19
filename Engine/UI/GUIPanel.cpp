#include "GUIPanel.h"

GUIPanel::GUIPanel(std::string name, std::string path, float x, float y)
	:
	GUIElement(name, {0,0,0,0},PANEL),
	surf(Surface::FromFile(path)),
	Alfa(false)
{
	Box.top = y;
	Box.bottom = y + surf.GetHeight();
	Box.left = x;
	Box.right = x + surf.GetWidth();
}

void GUIPanel::Draw(Graphics & gfx)
{
	if (Enabled) {
		if (Alfa) {
			surf.Draw(Box.left, Box.top, gfx);
		}
		else {
			surf.DrawAlfa(Box.left, Box.top, gfx);
		}
	}
}
