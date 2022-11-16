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

	void ComboA();
	void ComboB();

public:
	SDL_Texture* arrows_left = nullptr;
	SDL_Texture* arrows_mid = nullptr;
	SDL_Texture* combo_A = nullptr;
	SDL_Texture* trigger = nullptr;
	SDL_Texture* x10 = nullptr;

	bool arrows_left_ON = false;
	bool arrows_mid_ON = false;
	bool combo_right_ON = false;
	bool trigger_ON = false;
	bool x10_ON = false;

	int delayComboA;
	int delayComboB;
};