#pragma once

#include "Module.h"

#define DEBUG_BOX 225

class Debug : public Module
{
public:

	Debug(Application* app, bool start_enabled = true);
	virtual ~Debug();

	bool Start();
	update_status Update();	// Switch debug on/off
	update_status PostUpdate();		// Draw if debug true

	void DrawDebug();

public:
	//flags
	bool debug;
	bool variables = false;
	bool camLimits = false;
	bool godMode = false;
	bool freeCam = false;
	bool teleport = false;

private:


};