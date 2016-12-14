#include "TextInput.h"

void TextInput::Update(Mouse& _mouse, Keyboard& kbd) {
	if (box.Overlaps(_mouse.GetPosX(), _mouse.GetPosY())) {
		_mouse.ChangeCursor(IDC_IBEAM);
	}
	else {
		_mouse.ChangeCursor(IDC_ARROW);
	}

	if (box.Overlaps(_mouse.GetPosX(), _mouse.GetPosY()) && _mouse.LeftIsPressed()) {
		Active = true;
		kbd.Flush();
		time(&last);
	}
	else if (_mouse.LeftIsPressed()) {
		Active = false;
	}

	if (Active) {
		while (!(kbd.CharIsEmpty())) {
			unsigned char txt = kbd.ReadChar();
			if ((txt >= '0' && txt <= '9' || txt >= 'A' && txt <= 'z') && text.size() < maxchar) {
				text.push_back(txt);
			}

			if (kbd.KeyIsPressed(VK_BACK) && text.size() > 0) {
				text.erase(text.end() - 1);
			}
		}
	}
}

void TextInput::Draw(Graphics& gfx) {
	if (placeholder.size() > 0) {
		if (!Active && text.size() <= 0) {
			gfx.DrawClipText(placeholder, box, font, phcolor);
		}
		if (text.size() > 0) {
			if (isPassword)
			{
				/*std::string todraw = "";
				char uni = '\u25CF';
				for (unsigned int i = 0; i < text.size(); i++) {
				todraw += uni;
				}*/
				//gfx.DrawClipText(todraw, box, font, Colors::Black);
				int len = text.size();
				float x = (box.GetHeight() / 2) - (dot.GetWidth() / 2) - ((box.GetHeight() / 10) * 2);
				float y = (box.GetHeight() / 2) - (dot.GetWidth() / 2);
				int fit = box.GetWidth() / (dot.GetWidth() + (box.GetHeight() / 10));
				if (len < fit) {
					for (unsigned int i = 0; i < len; i++) {
						float each = (dot.GetWidth() + (box.GetHeight() / 10)) * i;
						gfx.DrawSpriteAlfa(box.left + x + each, box.top + y, dot);
					}
				}
				else {
					for (int i = 0; i < fit; i++) {
						float each = (dot.GetWidth() + (box.GetHeight() / 10)) * i;
						gfx.DrawSpriteAlfa(box.left + x + each, box.top + y, dot);
					}
				}

			}
			else
			{
				gfx.DrawClipText(text, box, font, textcolor);
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
			gfx.DrawClipText(todraw, box, font, Colors::Black);*/
			int len = text.size();
			float x = (box.GetHeight() / 2) - (dot.GetWidth() / 2) - ((box.GetHeight() / 10) * 2);
			float y = (box.GetHeight() / 2) - (dot.GetWidth() / 2);
			int fit = box.GetWidth() / (dot.GetWidth() + (box.GetHeight() / 10));
			if (len < fit) {
				for (unsigned int i = 0; i < len; i++) {
					float each = (dot.GetWidth() + (box.GetHeight() / 10)) * i;
					gfx.DrawSpriteAlfa(box.left + x + each, box.top + y, dot);
				}
			}
			else {
				for (int i = 0; i < fit; i++) {
					float each = (dot.GetWidth() + (box.GetHeight() / 10)) * i;
					gfx.DrawSpriteAlfa(box.left + x + each, box.top + y, dot);
				}
			}

		}
		else
		{
			gfx.DrawClipText(text, box, font, textcolor);
		}
	}

	if (Active) {
		RectF rc = gfx.MeasureString(text, -1, font, box);
		int x;
		if (isPassword) {
			int fit = box.GetWidth() / (dot.GetWidth() + (box.GetHeight() / 10));
			if (text.size() < fit) {
				if (text.size() == 0) {
					x = rc.GetWidth() + (fontsize / 5);
				}
				else {
					x = (dot.GetWidth() + (box.GetHeight() / 10)) * text.size();
				}
			}
			else {
				x = box.GetWidth() - (box.GetHeight() / 10);
			}
		}
		else {
			if (box.GetWidth() > rc.GetWidth()) {
				if (text.size() > 0) {
					x = rc.GetWidth() - (fontsize / 5);
				}
				else {
					x = rc.GetWidth() + (fontsize / 5);
				}
			}
			else {
				x = box.GetWidth() - (box.GetHeight() / 10);
			}
		}
		int y = (box.GetHeight() / 2) - (fontsize / 2);
		DrawActiveCursor(box.left + x, box.top + y, gfx);
	}

	for (int i = box.left; i < box.right; i++) {
		gfx.PutPixel(i + 1, box.top, { 0,0,0 });
	}
	for (int i = box.left; i < box.right; i++) {
		gfx.PutPixel(i, box.bottom, { 0,0,0 });
	}
	for (int i = box.top; i < box.bottom; i++) {
		gfx.PutPixel(box.left, i, { 0,0,0 });
	}
	for (int i = box.top; i < box.bottom; i++) {
		gfx.PutPixel(box.right, i + 1, { 0,0,0 });
	}
}

void TextInput::DrawActiveCursor(int x, int y, Graphics & gfx)
{
	if (Blink()) {
		for (int i = 0; i < fontsize; i++) {
			gfx.PutPixel(x, y + i, phcolor);
		}
	}
}

bool TextInput::Blink() {
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






