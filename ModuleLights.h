#pragma once
#include "Module.h"
#include "Globals.h"
#include "Entity.h"


class ModuleLights : public Module
{
public:
	ModuleLights(Application* app, bool start_enabled);
	~ModuleLights();

	// Main module steps
	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void Arrows();
	void CircleBouncer();
	void TriangleBouncer();
	void ComboA();
	void ComboB();
	void Time();

public:
	SDL_Texture* arrows_left = nullptr;
	SDL_Texture* arrows_mid = nullptr;
	SDL_Texture* combo_A = nullptr;
	SDL_Texture* trigger = nullptr;
	SDL_Texture* x10 = nullptr;

	int delayBlue;
	int delayYellow;
	int delayRed;
	int delayTriLeft;
	int delayTriRight;
	int delayComboA;
	int delayComboB;
	int delayTime;
};