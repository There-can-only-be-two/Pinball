#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleWin : public Module
{
public:

	// Constructors & Destructors
	ModuleWin(Application* app, bool start_enabled = true);
	~ModuleWin();

	// Main module steps
	bool Start();
	update_status Update();
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

