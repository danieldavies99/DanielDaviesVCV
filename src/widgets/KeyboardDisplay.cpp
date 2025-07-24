#include "KeyboardDisplay.hpp"

using namespace rack;

void KeyboardDisplay::draw(const DrawArgs &args)
{
    if (!args.vg)
    {
        return;
    }

    int index = static_cast<int>(round((*mappedVoltage - (-10.0)) * 12));  // (shift to 0V, then scale)
    index = quantize::clamp(index, 0, NUM_SEMITONES - 1);
    Key note = pitchClassLookup[index];

    if (!*on) return; // if off, don't draw

    // draw C
    if (note == KEY_C)
    {
        svgDraw(args.vg, keyOnC->handle);
    }

    // draw C#
    if (note == KEY_C_SHARP)
    {
        nvgTranslate(args.vg, mm2px(2.1), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw D
    if (note == KEY_D)
    {
        nvgTranslate(args.vg, mm2px(3.25), 0);
        svgDraw(args.vg, keyOnD->handle);
    }

    // draw D#
    if (note == KEY_D_SHARP)
    {
        nvgTranslate(args.vg, mm2px(2.1 + 3.8), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw E
    if (note == KEY_E)
    {
        nvgTranslate(args.vg, mm2px(3.25 * 2), 0);
        svgDraw(args.vg, keyOnE->handle);
    }

    // draw F
    if (note == KEY_F)
    {
        nvgTranslate(args.vg, mm2px(3.25 * 3), 0);
        svgDraw(args.vg, keyOnF->handle);
    }

    // draw F#
    if (note == KEY_F_SHARP)
    {
        nvgTranslate(args.vg, mm2px(2.1 + (9.6)), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw G
    if (note == KEY_G)
    {
        nvgTranslate(args.vg, mm2px(3.25 * 4), 0);
        svgDraw(args.vg, keyOnG->handle);
    }

    // draw G#
    if (note == KEY_G_SHARP)
    {
        nvgTranslate(args.vg, mm2px(2.1 + (13.35)), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw A
    if (note == KEY_A)
    {
        nvgTranslate(args.vg, mm2px(3.25 * 5), 0);
        svgDraw(args.vg, keyOnA->handle);
    }

    // draw A#
    if (note == KEY_A_SHARP)
    {
        nvgTranslate(args.vg, mm2px(2.1 + 16.95), 0);
        svgDraw(args.vg, keyOnSharp->handle);
    }

    // draw B
    if (note == KEY_B)
    {
        nvgTranslate(args.vg, mm2px(3.25 * 6), 0);
        svgDraw(args.vg, keyOnB->handle);
    }
};
