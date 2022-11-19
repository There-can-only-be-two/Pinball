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

	void CircleBouncer();
	void TriangleBouncer();
	void ComboA();
	void ComboB();
	void Time();
	void ArrowLeft();
	void ArrowMid_A();
	void ArrowMid_B();

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
	int delayArrowsMid_A;
	int delayArrowsMid_B;

	Animation* anim_CurrentTime = nullptr;
	Animation* anim_CurrentArrowsLeft = nullptr;
	Animation* anim_CurrentArrowsMid_A = nullptr;
	Animation* anim_CurrentArrowsMid_B = nullptr;
	Animation anim_Time;
	Animation anim_ArrowsLeft;
	Animation anim_ArrowsMid_A;
	Animation anim_ArrowsMid_B;
};