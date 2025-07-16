#include "DanielDavies.hpp"
#include "SetCableColorMenu.hpp"

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
		menu->addChild (new SetCableColorMenu());
	}
};

Model *modelBlank3 = createModel<Blank3, Blank3Widget>("Blank3");