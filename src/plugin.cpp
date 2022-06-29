#include "plugin.hpp"

Plugin* pluginInstance;

void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	p->addModel(modelSequel8Module);
	p->addModel(modelSequel16Module);
	p->addModel(modelSequelSave);
	p->addModel(modelQuantify);
	p->addModel(modelSamuel);
	p->addModel(modelBlank3);
	p->addModel(modelBlank5);
	p->addModel(modelBend);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
