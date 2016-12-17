#include "GUITextInput.h"

GUITextInput::GUITextInput(std::string name, float x, float y, int width, int height, std::wstring fontfamily)
	:
	GUIElement(name, { y, y + height, x, x + width }),
	fontsize((((float)height) / 3.5) * 2),
	font(fontfamily, fontsize, false),
	inputText(""),
	maxchar(20),
	isPassword(false),
	dot(Surface::FromFile("..\\data\\textures\\dot.png")),
	inputTextColor({ 0,0,0 }),
	phcolor({ 50,50,50 }),
	placeholder("")
{
}

void GUITextInput::Update(Mouse* _mouse, Keyboard* kbd) {
	GUIElement::Update(_mouse,kbd);
	if (LMB) {
		Active = true;
		kbd->Flush();
		time(&last);
	} 
	else if (!Hover && _mouse->LeftIsPressed()) {
		Active = false;
	}

	if (Active) {
		while (!(kbd->CharIsEmpty())) {
			unsigned char txt = kbd->ReadChar();
			if ((txt >= '0' && txt <= '9' || txt >= 'A' && txt <= 'z') && inputText.size() < maxchar) {
				inputText.push_back(txt);
			}

			if (kbd->KeyIsPressed(VK_BACK) && inputText.size() > 0) {
				inputText.erase(inputText.end() - 1);
			}
		}
	}
}

void GUITextInput::Draw(Graphics& gfx) {
	if (placeholder.size() > 0) {
		if (!Active && inputText.size() <= 0) {
			gfx.DrawClipText(placeholder, Box, font, phcolor);
		}
		if (inputText.size() > 0) {
			if (isPassword)
			{
				/*std::string todraw = "";
				char uni = '\u25CF';
				for (unsigned int i = 0; i < text.size(); i++) {
				todraw += uni;
				}*/
				//gfx.DrawClipText(todraw, Box, font, Colors::Black);
				int len = inputText.size();
				float x = (Box.GetHeight() / 2) - (dot.GetWidth() / 2) - ((Box.GetHeight() / 10) * 2);
				float y = (Box.GetHeight() / 2) - (dot.GetWidth() / 2);
				int fit = Box.GetWidth() / (dot.GetWidth() + (Box.GetHeight() / 10));
				if (len < fit) {
					for (unsigned int i = 0; i < len; i++) {
						float each = (dot.GetWidth() + (Box.GetHeight() / 10)) * i;
						gfx.DrawSpriteAlfa(Box.left + x + each, Box.top + y, dot);
					}
				}
				else {
					for (int i = 0; i < fit; i++) {
						float each = (dot.GetWidth() + (Box.GetHeight() / 10)) * i;
						gfx.DrawSpriteAlfa(Box.left + x + each, Box.top + y, dot);
					}
				}

			}
			else
			{
				gfx.DrawClipText(inputText, Box, font, inputTextColor);
			}
		}
	}
	else
	{
		if (isPassword)
		{
			/*std::string todraw = "";
			char uni = '\u25CF';
			for (unsigned int i = 0; i < text.size(); i++) {
			todraw += uni;
			}
			gfx.DrawClipText(todraw, Box, font, Colors::Black);*/
			int len = inputText.size();
			float x = (Box.GetHeight() / 2) - (dot.GetWidth() / 2) - ((Box.GetHeight() / 10) * 2);
			float y = (Box.GetHeight() / 2) - (dot.GetWidth() / 2);
			int fit = Box.GetWidth() / (dot.GetWidth() + (Box.GetHeight() / 10));
			if (len < fit) {
				for (unsigned int i = 0; i < len; i++) {
					float each = (dot.GetWidth() + (Box.GetHeight() / 10)) * i;
					gfx.DrawSpriteAlfa(Box.left + x + each, Box.top + y, dot);
				}
			}
			else {
				for (int i = 0; i < fit; i++) {
					float each = (dot.GetWidth() + (Box.GetHeight() / 10)) * i;
					gfx.DrawSpriteAlfa(Box.left + x + each, Box.top + y, dot);
				}
			}

		}
		else
		{
			gfx.DrawClipText(inputText, Box, font, inputTextColor);
		}
	}

	if (Active) {
		RectF rc = gfx.MeasureString(inputText, -1, font, Box);
		int x;
		if (isPassword) {
			int fit = Box.GetWidth() / (dot.GetWidth() + (Box.GetHeight() / 10));
			if (inputText.size() < fit) {
				if (inputText.size() == 0) {
					x = rc.GetWidth() + (fontsize / 5);
				}
				else {
					x = (dot.GetWidth() + (Box.GetHeight() / 10)) * inputText.size();
				}
			}
			else {
				x = Box.GetWidth() - (Box.GetHeight() / 10);
			}
		}
		else {
			if (Box.GetWidth() > rc.GetWidth()) {
				if (inputText.size() > 0) {
					x = rc.GetWidth() - (fontsize / 5);
				}
				else {
					x = rc.GetWidth() + (fontsize / 5);
				}
			}
			else {
				x = Box.GetWidth() - (Box.GetHeight() / 10);
			}
		}
		int y = (Box.GetHeight() / 2) - (fontsize / 2);
		DrawActiveCursor(Box.left + x, Box.top + y, gfx);
	}
	GUIElement::Draw(gfx);
}

void GUITextInput::DrawActiveCursor(int x, int y, Graphics & gfx)
{
	if (Blink()) {
		for (int i = 0; i < fontsize; i++) {
			gfx.PutPixel(x, y + i, inputTextColor);
		}
	}
}

bool GUITextInput::Blink() {
	time_t now;
	time(&now);
	if ((now - last) == 1) {
		seccount++;
		last = now;
	}
	if (seccount % 2) {
		return true;
	}
	else {
		return false;
	}
}






