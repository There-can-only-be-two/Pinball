#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include <list>
#include "SString.h"

struct Scores {
	SString name;
	int score;
};

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
	list<Scores> ranking = { {"XAVI", 100000}, {"HECTOR", 99000}, {"JULS", 69000}, {"JAN", 42000}, {"YOU", 0} };

	// Textures
	SDL_Texture* img;
	int font;
	
	// FX
	uint highScore;
	// to store each highscore
	uint* ranks;
};
