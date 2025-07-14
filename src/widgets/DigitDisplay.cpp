#include "DigitDisplay.hpp"
using namespace rack;

std::string DigitDisplay::formatDigitValue(int value)
{
    std::string res = std::to_string(value);
    while (res.length() < numDigits)
    {
        res = "@" + res; // where @ is off
    }
    return res;
};

void DigitDisplay::draw(const DrawArgs &args)
{
    if (!args.vg)
    {
        return;
    }
    nvgBeginPath(args.vg);
    nvgRoundedRect(args.vg, 0, mm2px(-1), mm2px(1.f + (numDigits * 3.75)), mm2px(7), 1);
    nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
    nvgFill(args.vg);
    std::string twoDigitValue = formatDigitValue(*value);
    for (std::string::size_type i = 0; i < twoDigitValue.length(); i++)
    {
        if (*showDashes)
        {
            svgDraw(args.vg, digitDash->handle);
            nvgTranslate(args.vg, mm2px(3.6), 0);
            continue;
        }
        switch (twoDigitValue[i])
        {
        case '@':
            svgDraw(args.vg, digitOff->handle);
            break;
        case '0':
            svgDraw(args.vg, digit0->handle);
            break;
        case '1':
            svgDraw(args.vg, digit1->handle);
            break;
        case '2':
            svgDraw(args.vg, digit2->handle);
            break;
        case '3':
            svgDraw(args.vg, digit3->handle);
            break;
        case '4':
            svgDraw(args.vg, digit4->handle);
            break;
        case '5':
            svgDraw(args.vg, digit5->handle);
            break;
        case '6':
            svgDraw(args.vg, digit6->handle);
            break;
        case '7':
            svgDraw(args.vg, digit7->handle);
            break;
        case '8':
            svgDraw(args.vg, digit8->handle);
            break;
        case '9':
            svgDraw(args.vg, digit9->handle);
            break;
        default:
            svgDraw(args.vg, digit1->handle);
        }
        nvgTranslate(args.vg, mm2px(3.6), 0);
    }
};
