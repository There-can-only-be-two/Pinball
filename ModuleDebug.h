#pragma once

#include "Module.h"
#include <chrono>
using namespace std::chrono;

#define DEBUG_BOX 225

class ModuleDebug : public Module
{
public:

	ModuleDebug(Application* app, bool start_enabled = true);
	virtual ~ModuleDebug();

	bool Start();
	update_status Update();	// Switch debug on/off
	update_status PostUpdate();		// Draw if debug true

	void DrawDebug();
	void DrawPhysics();

public:
	//flags
	bool drawDebug = false;
	bool drawPhysics = false;
	bool variables = false;
	bool lightsON = false;
	bool musicON = false;
	bool sfxON = true;
	bool changeUI = false;

	microseconds timePerCycle;
	microseconds elapsedFrame;
	int desiredFPSmic;
	int desiredFPS = 60;

};