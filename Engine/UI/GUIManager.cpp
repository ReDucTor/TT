#include "GUIManager.h"
#include "GUITextInput.h"
#include "GUIButton.h"
#include "GUIPanel.h"

GUIManager::GUIManager(Mouse * ms, Keyboard * kbd)
	:
	kbd(kbd),
	_mouse(ms)
{
}

GUIManager::~GUIManager()
{
	Elements.clear();
}

void GUIManager::AddTextInput(std::string name, float x, float y, int width, int height, std::wstring fontfamily)
{
	Elements.emplace_back(std::make_shared<GUITextInput>(name, x, y, width, height, fontfamily));
}

void GUIManager::AddButton(std::string name, std::string title, std::string path, float x, float y, std::wstring font, float fontsize, bool textbold)
{
	Elements.emplace_back(std::make_shared<GUIButton>(name, title, path, x, y, font, fontsize, textbold));
}

void GUIManager::AddCheckBox()
{
}

void GUIManager::AddList()
{
}

void GUIManager::AddPanel(std::string name, std::string path, float x, float y)
{
	Elements.emplace_back(std::make_shared<GUIPanel>(name, path, x, y));
}

void GUIManager::Draw(Graphics & gfx)
{
	for (auto i : Elements) {
		i->Draw(gfx);
	}
}

void GUIManager::Update()
{
	int ti = 0;//text input
	int bt = 0;// buttons
	for (auto i : Elements) {
		i->Update(_mouse, kbd);
		switch (i->GetType()) {
			case GUIElement::eType::TEXTINPUT:
				if (i->IsHover())
					ti++;
				break;
			case GUIElement::eType::BUTTON:
				if (i->IsHover())
					bt++;
				break;
		}
	}
	if (ti > 0) {
		_mouse->ChangeCursor(IDC_IBEAM);
	}
	else if (bt > 0) {
		_mouse->ChangeCursor(IDC_HAND);
	}
	else {
		_mouse->ChangeCursor(IDC_ARROW);
	}
}

void GUIManager::ClearGUI()
{
	Elements.clear();
}

std::shared_ptr<GUIElement> GUIManager::GetElement(std::string name)
{
	for (auto i : Elements) {
		if (i->GetName() == name) {
			return i;
		}
	}
	return nullptr;
}
