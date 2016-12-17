#pragma once
#include <vector>
#include "GUIElement.h"
#include "..\Framework\Keyboard.h"
#include "..\Framework\Mouse.h"


class GUIManager {
public:
	GUIManager(Mouse* ms,Keyboard* kbd);
	~GUIManager();
	void AddTextInput(std::string name, float x, float y, int width, int height, std::wstring fontfamily = L"Minion Pro");
	void AddButton();
	void AddCheckBox();
	void AddList();
	void AddPanel();
	void Draw(Graphics& gfx);
	void Update();
	void ClearGUI();
	std::shared_ptr<GUIElement> GetElement(std::string name);
private:
	Mouse* mouse;
	Keyboard* kbd;
	std::vector<std::shared_ptr<GUIElement>> Elements;
};