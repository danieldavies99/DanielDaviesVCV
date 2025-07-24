#pragma once
#include <rack.hpp>
#include "DanielDavies.hpp"
#include "utilities/Quantize.hpp"

static constexpr int NUM_SEMITONES = 241;  // From -10V to +10V (inclusive)
static constexpr int SEMITONES_PER_OCTAVE = 12;

// as in, keys on a keyboard
enum Key
{
    KEY_C,
    KEY_C_SHARP,
    KEY_D,
    KEY_D_SHARP,
    KEY_E,
    KEY_F,
    KEY_F_SHARP,
    KEY_G,
    KEY_G_SHARP,
    KEY_A,		
    KEY_A_SHARP,
    KEY_B,
};

static std::array<Key, NUM_SEMITONES> pitchClassLookup = [] {
	std::array<Key, NUM_SEMITONES> lookup{};
	for (int i = 0; i < NUM_SEMITONES; ++i) {
		lookup[i] = static_cast<Key>(i % SEMITONES_PER_OCTAVE);
	}
	return lookup;
}();

struct KeyboardDisplay : SvgWidget
{
    std::shared_ptr<rack::Svg> keyOnC = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/widgets/KeyOnC.svg"));
    std::shared_ptr<rack::Svg> keyOnD = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/widgets/KeyOnD.svg"));
    std::shared_ptr<rack::Svg> keyOnE = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/widgets/KeyOnE.svg"));
    std::shared_ptr<rack::Svg> keyOnF = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/widgets/KeyOnF.svg"));
    std::shared_ptr<rack::Svg> keyOnG = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/widgets/KeyOnG.svg"));
    std::shared_ptr<rack::Svg> keyOnA = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/widgets/KeyOnA.svg"));
    std::shared_ptr<rack::Svg> keyOnB = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/widgets/KeyOnB.svg"));
    std::shared_ptr<rack::Svg> keyOnSharp = rack::Svg::load(rack::asset::plugin(pluginInstance, "res/widgets/KeyOnSharp.svg"));

    double *mappedVoltage = 0;
    bool *on = 0;

    KeyboardDisplay() {}

    void draw(const DrawArgs &args) override;

private:
    std::string formatDigitValue(int value);
};