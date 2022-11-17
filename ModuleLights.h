#pragma once
#include "Module.h"
#include "Globals.h"
#include "Entity.h"
#include "Animation.h"


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

	void ArrowLeft();
	void ArrowMid();
	void CircleBouncer();
	void TriangleBouncer();
	void ComboA();
	void ComboB();
	void Time();

	void LoadAnimations();


public:
	SDL_Texture* arrows_left = nullptr;
	SDL_Texture* arrows_mid_A = nullptr;
	SDL_Texture* arrows_mid_B = nullptr;
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
	int delayArrowsLeft;
	int delayArrowsMid;

	Animation* anim_Current = nullptr;
	Animation anim_ArrowsMid;
};