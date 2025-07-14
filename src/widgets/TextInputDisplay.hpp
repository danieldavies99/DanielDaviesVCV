#pragma once

#include "CharacterDisplay.hpp"

struct TextInputDisplay : CharacterDisplay
{
	TextInputDisplay()
	{
		numPixelsX = 83; // should be multiple of six minus one for letters
		numPixelsY = 47; // should be multiple of eight minus one for letters
	}
	bool isSelected = false;
	bool shouldShowCursor = true;
	int framesSinceLastCursorChange = 0;
	std::string *message;

	void onButton(const ButtonEvent &e) override;
	void onSelectKey(const SelectKeyEvent &e) override;
	void onSelect(const SelectEvent &e) override;
	void onDeselect(const DeselectEvent &e) override;

	void drawCursor(int x, int y);
	void drawMessage();
	void process() override;
};