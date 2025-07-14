#pragma once
#include <array>
#include <rack.hpp>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
extern Model *modelSequel8;
extern Model *modelSequel16;
extern Model *modelSequelSave;
extern Model *modelQuantify;
extern Model *modelSamuel;
extern Model *modelBlank3;
extern Model *modelBlank5;
extern Model *modelBend;
extern Model *modelJames;
extern Model *modelKnot;


// Timing Utils


struct KnotUndoState
{
	int output1Index;
	int output2Index;
	int output3Index;
	int output4Index;

	KnotUndoState(int output1Index, int output2Index, int output3Index, int output4Index)
	{
		this->output1Index = output1Index;
		this->output2Index = output2Index;
		this->output3Index = output3Index;
		this->output4Index = output4Index;
	}
};
