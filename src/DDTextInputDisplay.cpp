#include "plugin.hpp"
#include <functional>

using namespace rack;

void TextInputDisplay::process() {
    drawMessage();
}

void TextInputDisplay::drawMessage() {
    darkenAll();
    if(message->size() < 1) {
        drawCursor(0,0);
        return;
    }
    std::transform(message->begin(), message->end(),message->begin(), ::toupper);
    for(int i = 0; i < (int)message->size(); i++) {
        int lineLength = (numPixelsX + 1)/6;
        int lineNum = floor(i / lineLength);
        drawLetter((*message)[i], (i - lineNum*lineLength)*6, lineNum * 8);

        int cursorLineNum = floor( (i + 1) / lineLength);
        // DEBUG(std::to_string(cursorLineNum).c_str());
        if(i == (int)message->size() - 1) {
            drawCursor((i + 1 - cursorLineNum*lineLength)*6, cursorLineNum * 8);
        }
    }
}

void TextInputDisplay::onButton(const ButtonEvent& e) {
    e.consume(this);
};

void TextInputDisplay::onSelect(const SelectEvent& e) {
    isSelected = true;
    e.consume(this);
}

void TextInputDisplay::onDeselect(const DeselectEvent& e) {
    isSelected = false;
}

void TextInputDisplay::onSelectKey(const SelectKeyEvent& e)
{   
    e.consume(this);
    if(e.action == GLFW_PRESS)
	{
		// do stuff
        if(e.key > 47 && e.key < 59 )  { // 0 - 9
            message->append(e.keyName);
        }
        if(e.key > 64 && e.key < 91 )  { // A - Z
            message->append(e.keyName);
        }
        if(e.key == GLFW_KEY_SPACE) {
            message->append(" ");
        }
        if(e.key == GLFW_KEY_BACKSPACE) { // backspace
            if(message->size() > 0) {
                message->pop_back();
            }
            e.consume(this);
        }
	}
}


void TextInputDisplay::drawCursor(int x, int y) {
    if(shouldShowCursor && isSelected) {
        lightPixel(0, 0, x, y);
        lightPixel(0, 1, x, y);
        lightPixel(0, 2, x, y);
        lightPixel(0, 3, x, y);
        lightPixel(0, 4, x, y);
        lightPixel(0, 5, x, y);
        lightPixel(0, 6, x, y);
    }
    if(framesSinceLastCursorChange > 100) {
        shouldShowCursor = !shouldShowCursor;
        framesSinceLastCursorChange = 0;
    }
    framesSinceLastCursorChange++;
}