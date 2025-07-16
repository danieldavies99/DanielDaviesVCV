#include "DanielDavies.hpp"
#include "utilities/SafeMenuItem.hpp"

struct Blank3 : Module
{
	enum ParamId
	{
		PARAMS_LEN
	};
	enum InputId
	{
		INPUTS_LEN
	};
	enum OutputId
	{
		OUTPUTS_LEN
	};
	enum LightId
	{
		LIGHTS_LEN
	};

	Blank3()
	{
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
	}

	void process(const ProcessArgs &args) override
	{
	}
};

struct Blank3Widget : ModuleWidget
{

	Blank3Widget(Blank3 *module)
	{
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/panels/light/Blank3.svg")));
	}

	void appendContextMenu(Menu *menu) override
	{
		menu->addChild(new MenuSeparator());
		std::string selectedColorScheme = rack::settings::preferDarkPanels ? "Dark" : "Light";
		menu->addChild (new SafeMenuItem (
            "Use DD cable color scheme - " + selectedColorScheme,
            [=] {
				if(rack::settings::preferDarkPanels) {
					rack::settings::cableColors = std::vector<NVGcolor>{
						// nvgRGB(11, 32, 39), // dark panel color
						nvgRGB(69, 105, 144), // alt dark color (avoid using dark panel color because hard to see on dark panel)
						nvgRGB(237, 106, 90), // orange
						nvgRGB(155, 193, 188), // green
						nvgRGB(244, 241, 187), // yellow
						nvgRGB(249, 250, 251), // light panel color
					};
				} else {
					rack::settings::cableColors = std::vector<NVGcolor>{
						nvgRGB(11, 32, 39), // dark panel color
						nvgRGB(237, 106, 90), // orange
						nvgRGB(155, 193, 188), // green
						nvgRGB(244, 241, 187), // yellow
						// nvgRGB(249, 250, 251), // light panel color
						nvgRGB(89, 95, 114), // alt light color (avoid using light panel color because hard to see on light panels)
					};
				}
			},
            true,
			"This option will override your current cable color scheme."
        ));
	}
};

Model *modelBlank3 = createModel<Blank3, Blank3Widget>("Blank3");