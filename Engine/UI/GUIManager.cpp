#include "GUIManager.h"
#include "GUITextInput.h"

GUIManager::GUIManager(Mouse * ms, Keyboard * kbd)
	:
	kbd(kbd),
	mouse(ms)
{
}

GUIManager::~GUIManager()
{
	Elements.clear();
}

void GUIManager::AddTextInput(std::string name, float x, float y, int width, int height, std::wstring fontfamily)
{
	Elements.emplace_back(std::make_unique<GUITextInput>(name, x, y, width, height, fontfamily));
}

void GUIManager::AddButton()
{
}

void GUIManager::AddCheckBox()
{
}

void GUIManager::AddList()
{
}

void GUIManager::AddPanel()
{
}

void GUIManager::Draw(Graphics & gfx)
{
	for (auto i : Elements) {
		i->Draw(gfx);
	}
}

void GUIManager::Update()
{
	for (auto i : Elements) {
		i->Update(mouse, kbd);
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
	return false;
}

