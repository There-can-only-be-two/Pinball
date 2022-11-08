#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleTitle : public Module
{
public:

	// Constructors & Destructors
	ModuleTitle(Application* app, bool start_enabled = true);
	~ModuleTitle();

	// Main module steps
	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:

	// Lists of physics objects


	// Textures
	SDL_Texture* img;

	// FX
	uint highscore, currentscore;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};
