#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleDeath : public Module
{
public:

	// Constructors & Destructors
	ModuleDeath(Application* app, bool start_enabled);
	~ModuleDeath();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();

public:

	// Lists of physics objects


	// Textures
	SDL_Texture* img;
	int font;

	// FX
	uint highscore, currentscore;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};
