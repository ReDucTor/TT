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
	void AddButton(std::string name, std::string title, std::string path, float x, float y, int width, int height, std::wstring font, float fontsize, bool textbold);
	void AddCheckBox();
	void AddList();
	void AddPanel();
	void Draw(Graphics& gfx);
	void Update();
	void ClearGUI();
	std::shared_ptr<GUIElement> GetElement(std::string name);
private:
	Mouse* _mouse;
	Keyboard* kbd;
	std::vector<std::shared_ptr<GUIElement>> Elements;
};