#include "KeyboardDisplay.hpp"

using namespace rack;

void KeyboardDisplay::draw(const DrawArgs &args)  {
    if(!args.vg) {
    	return;
    }

    if(*keyOnValue == KEY_ON_C) {
        svgDraw(args.vg, keyOnC->handle);
    }

    // draw D
    if(*keyOnValue == KEY_ON_D) {
        nvgTranslate(args.vg, mm2px(3.25), 0);
        svgDraw(args.vg, keyOnD->handle);
    }

    // draw E
    if(*keyOnValue == KEY_ON_E) {
        nvgTranslate(args.vg, mm2px(3.25*2), 0);
        svgDraw(args.vg, keyOnE->handle);
    }

    // draw F
    if(*keyOnValue == KEY_ON_F) {
        nvgTranslate(args.vg, mm2px(3.25*3), 0);
        svgDraw(args.vg, keyOnF->handle);
    }

    // draw G
    if(*keyOnValue == KEY_ON_G) {
        nvgTranslate(args.vg, mm2px(3.25*4), 0);
        svgDraw(args.vg, keyOnG->handle);
    }

    // draw A
    if(*keyOnValue == KEY_ON_A) {
        nvgTranslate(args.vg, mm2px(3.25*5), 0);
        svgDraw(args.vg, keyOnA->handle);
    }

    // draw B
    if(*keyOnValue == KEY_ON_B) {
        nvgTranslate(args.vg, mm2px(3.25*6), 0);
        svgDraw(args.vg, keyOnB->handle);
    }

    // draw c#
    if(*keyOnValue == KEY_ON_C_SHARP) {
        nvgTranslate(args.vg, mm2px(2.1), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw d#
    if(*keyOnValue == KEY_ON_D_SHARP) {
        nvgTranslate(args.vg, mm2px(2.1 + 3.8), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw f#
    if(*keyOnValue == KEY_ON_F_SHARP) {
        nvgTranslate(args.vg, mm2px(2.1 + (9.6) ), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw g#
    if(*keyOnValue == KEY_ON_G_SHARP) {
        nvgTranslate(args.vg, mm2px(2.1 + (13.35) ), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw a#
    if(*keyOnValue == KEY_ON_A_SHARP) {
        nvgTranslate(args.vg, mm2px(2.1 + 16.95 ), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }
};
