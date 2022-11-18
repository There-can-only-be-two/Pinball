#include "ModuleLights.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleDebug.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "Animation.h"
#include "Flippers.h"
#include "Ball.h"
#include "Module.h"

ModuleLights::ModuleLights(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleLights::~ModuleLights() {}

bool ModuleLights::Start()
{
	arrows_left = App->textures->Load("pinball/Lights/arrows_left.png");
	arrows_mid_A = App->textures->Load("pinball/Lights/arrows_mid_A.png");
	arrows_mid_B = App->textures->Load("pinball/Lights/arrows_mid_B.png");
	combo_A = App->textures->Load("pinball/Lights/combo_A.png");
	trigger = App->textures->Load("pinball/Lights/trigger.png");
	x10 = App->textures->Load("pinball/Lights/x10.png");


	LoadAnimations();

	return true;
}

update_status ModuleLights::Update()
{
	if (App->debug->lightsON)
	{
		App->scene_intro->sensorBlue_Sensed = true;
		App->scene_intro->sensorYellow_Sensed = true;
		App->scene_intro->sensorRed_Sensed = true;

		App->scene_intro->sensorTriLeft_Sensed = true;
		App->scene_intro->sensorTriRight_Sensed = true;

		App->scene_intro->sensorTime_Sensed = true;
		//App->scene_intro->sensorX10_Sensed = true;

		App->scene_intro->sensorComboA1_Sensed = true;
		App->scene_intro->sensorComboA2_Sensed = true;
		App->scene_intro->sensorComboA3_Sensed = true;
		App->scene_intro->sensorComboB1_Sensed = true;
		App->scene_intro->sensorComboB2_Sensed = true;
		App->scene_intro->sensorComboB3_Sensed = true;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleLights::PostUpdate()
{
	ArrowLeft();
	ArrowMid();

	CircleBouncer();
	TriangleBouncer();

	ComboA();
	ComboB();
	Time();

	return UPDATE_CONTINUE;
}

bool ModuleLights::CleanUp()
{
	App->textures->Unload(arrows_left);
	App->textures->Unload(arrows_mid_A);
	App->textures->Unload(arrows_mid_B);
	App->textures->Unload(combo_A);
	App->textures->Unload(trigger);
	App->textures->Unload(x10);
	return true;
}

void ModuleLights::ArrowLeft()
{
	if (App->scene_intro->sensorBlue_Sensed)
	{
		delayArrowsLeft = 120;
		anim_Current = &anim_ArrowsLeft;
		App->scene_intro->sensorBlue_Sensed = false;
	}

	if (delayArrowsLeft > 0)
	{
		SDL_Rect rectArrowsLeft = anim_Current->GetCurrentFrame();
		App->renderer->Blit(arrows_left, 31, 99, &rectArrowsLeft);
		anim_Current->Update();

		delayArrowsLeft--;
	}
}

void ModuleLights::ArrowMid()
{
	if (true)
	{
		SDL_Rect rect = { 0, 0, 48, 148 };
		App->renderer->Blit(arrows_mid_A, 231, 522, &rect);
	}
	else
	{
		SDL_Rect rect = { 48, 0, 48, 148 };
		App->renderer->Blit(arrows_mid_A, 231, 522, &rect);
	}
}

void ModuleLights::CircleBouncer()
{
	//BLUE
	SDL_Rect rectBlue;
	if (App->scene_intro->sensorBlue_Sensed)
	{
		delayBlue = 6;
		App->scene_intro->sensorBlue_Sensed = false;
	}
	if (delayBlue > 0)
	{
		rectBlue = { 91, 2, 52, 52 }; //on
		delayBlue--;
	}
	else
		rectBlue = { 144, 2, 52, 52 }; //off
	
	App->renderer->Blit(App->scene_intro->assets, 202, 209, &rectBlue);


	//YELLOW
	SDL_Rect rectYellow;
	if (App->scene_intro->sensorYellow_Sensed)
	{
		delayYellow = 6;
		App->scene_intro->sensorYellow_Sensed = false;
	}
	if (delayYellow > 0)
	{
		rectYellow = { 196, 2, 52, 52 }; //on
		delayYellow--;
	}
	else
		rectYellow = { 249, 2, 52, 52 }; //off

	App->renderer->Blit(App->scene_intro->assets, 258, 306, &rectYellow);


	//RED
	SDL_Rect rectRed;
	if (App->scene_intro->sensorRed_Sensed)
	{
		delayRed = 6;
		App->scene_intro->sensorRed_Sensed = false;
	}
	if (delayRed > 0)
	{
		rectRed = { 303, 2, 52, 52 }; //on
		delayRed--;
	}
	else
		rectRed = { 357, 2, 52, 52 }; //off

	App->renderer->Blit(App->scene_intro->assets, 315, 209, &rectRed);
}

void ModuleLights::TriangleBouncer()
{
	//TRI LEFT
	SDL_Rect rectTriLeft;
	if (App->scene_intro->sensorTriLeft_Sensed)
	{
		delayTriLeft = 6;
		App->scene_intro->sensorTriLeft_Sensed = false;
	}
	if (delayTriLeft > 0)
	{
		rectTriLeft = { 280, 210, 76, 118 }; //on
		delayTriLeft--;
	}
	else
		rectTriLeft = { 280, 91, 76, 118 }; //off

	App->renderer->Blit(App->scene_intro->assets, 95, 527, &rectTriLeft);
	

	//TRI RIGHT
	SDL_Rect rectTriRight;
	if (App->scene_intro->sensorTriRight_Sensed)
	{
		delayTriRight = 6;
		App->scene_intro->sensorTriRight_Sensed = false;
	}
	if (delayTriRight > 0)
	{
		rectTriRight = { 365, 210, 76, 118 }; //on
		delayTriRight--;
	}
	else
		rectTriRight = { 365, 91, 76, 118 }; //off

	App->renderer->Blit(App->scene_intro->assets, 342, 527, &rectTriRight);

}

void ModuleLights::ComboA()
{
	SDL_Rect rect = { 0, 0, 27, 100 };
	App->renderer->Blit(combo_A, 426, 228, &rect);

	if (delayComboA == 0)
	{
		if (App->scene_intro->sensorComboA1_Sensed)
		{
			SDL_Rect rect = { 27, 0, 27, 30 };
			App->renderer->Blit(combo_A, 426, 228, &rect);
		}
		if (App->scene_intro->sensorComboA2_Sensed)
		{
			SDL_Rect rect = { 27, 30, 27, 33 };
			App->renderer->Blit(combo_A, 426, 258, &rect);
		}
		if (App->scene_intro->sensorComboA3_Sensed)
		{
			SDL_Rect rect = { 27, 63, 27, 37 };
			App->renderer->Blit(combo_A, 426, 291, &rect);
		}
		if (App->scene_intro->sensorComboA1_Sensed &&
			App->scene_intro->sensorComboA2_Sensed &&
			App->scene_intro->sensorComboA3_Sensed)
		{
			delayComboA = 180;
			App->scene_intro->currentScore += App->scene_intro->AddScore(2000);
			App->scene_intro->scoreMultiplier *= 2;
		}
	}
	else
	{
		if (delayComboA % 20 < 7)
		{
			SDL_Rect rect = { 27, 63, 27, 37 };
			App->renderer->Blit(combo_A, 426, 291, &rect);
		}
		else if (delayComboA % 20 > 12)
		{
			SDL_Rect rect = { 27, 0, 27, 30 };
			App->renderer->Blit(combo_A, 426, 228, &rect);
		}
		else
		{
			SDL_Rect rect = { 27, 30, 27, 33 };
			App->renderer->Blit(combo_A, 426, 258, &rect);
		}

		if (delayComboA == 1)
		{
			App->scene_intro->sensorComboA1_Sensed = false;
			App->scene_intro->sensorComboA2_Sensed = false;
			App->scene_intro->sensorComboA3_Sensed = false;
		}

		delayComboA--;
	}
}

void ModuleLights::ComboB()
{
	SDL_Rect rect = { 0, 0, 9, 53 };
	App->renderer->Blit(trigger, 225, 112, &rect);
	App->renderer->Blit(trigger, 281, 112, &rect);
	App->renderer->Blit(trigger, 337, 112, &rect);

	if (delayComboB == 0)
	{
		SDL_Rect rect = { 9, 0, 9, 53 };

		if (App->scene_intro->sensorComboB1_Sensed)
			App->renderer->Blit(trigger, 225, 112, &rect);

		if (App->scene_intro->sensorComboB2_Sensed)
			App->renderer->Blit(trigger, 281, 112, &rect);

		if (App->scene_intro->sensorComboB3_Sensed)
			App->renderer->Blit(trigger, 337, 112, &rect);

		if (App->scene_intro->sensorComboB1_Sensed &&
			App->scene_intro->sensorComboB2_Sensed &&
			App->scene_intro->sensorComboB3_Sensed)
		{
			delayComboB = 600; //10sec at 60FPS
			App->scene_intro->currentScore += App->scene_intro->AddScore(5000);
		}
	}
	else
	{
		if (delayComboB % 20 < 10)
		{
			SDL_Rect rect = { 0, 0, 9, 53 };
			App->renderer->Blit(trigger, 225, 112, &rect);
			App->renderer->Blit(trigger, 281, 112, &rect);
			App->renderer->Blit(trigger, 337, 112, &rect);
		}
		else
		{
			SDL_Rect rect = { 9, 0, 9, 53 };
			App->renderer->Blit(trigger, 225, 112, &rect);
			App->renderer->Blit(trigger, 281, 112, &rect);
			App->renderer->Blit(trigger, 337, 112, &rect);
		}

		if (delayComboB == 1)
		{
			App->scene_intro->sensorComboB1_Sensed = false;
			App->scene_intro->sensorComboB2_Sensed = false;
			App->scene_intro->sensorComboB3_Sensed = false;
		}

		delayComboB--;
	}
}

void ModuleLights::Time()
{
	SDL_Rect rect;

	if (delayTime == 0)
	{
		rect = { 501, 248, 50, 50 };
		App->renderer->Blit(App->scene_intro->assets, 88, 430, &rect);

		if (App->scene_intro->sensorTime_Sensed)
		{
			delayTime = 120;
			App->scene_intro->sensorTime_Sensed = false;
		}
	}
	else
	{		
		if (delayTime % 20 > 10)
			rect = { 444, 248, 50, 50 };
		else
			rect = { 501, 248, 50, 50 };

		App->renderer->Blit(App->scene_intro->assets, 88, 430, &rect);

		delayTime--;
	}
}

void ModuleLights::LoadAnimations()
{
	//Arrow Left
	anim_ArrowsLeft.PushBack({   0, 0, 128, 275 });
	anim_ArrowsLeft.PushBack({ 128, 0, 128, 275 });
	anim_ArrowsLeft.PushBack({ 256, 0, 128, 275 });
	anim_ArrowsLeft.PushBack({ 384, 0, 128, 275 });
	anim_ArrowsLeft.PushBack({ 512, 0, 128, 275 });
	anim_ArrowsLeft.PushBack({ 640, 0, 128, 275 });
	anim_ArrowsLeft.PushBack({ 768, 0, 128, 275 });
	anim_ArrowsLeft.PushBack({ 896, 0, 128, 275 });
	anim_ArrowsLeft.speed = 0.3f;
	anim_ArrowsLeft.loop;

	//Arrow Mid
	anim_ArrowsMid_A.PushBack({ 0, 0, 128, 275 });
	anim_ArrowsMid_A.PushBack({ 128, 0, 128, 275 });
	anim_ArrowsMid_A.PushBack({ 256, 0, 128, 275 });
	anim_ArrowsMid_A.PushBack({ 384, 0, 128, 275 });
	anim_ArrowsMid_A.PushBack({ 512, 0, 128, 275 });
	anim_ArrowsMid_A.PushBack({ 640, 0, 128, 275 });
	anim_ArrowsMid_A.PushBack({ 768, 0, 128, 275 });
	anim_ArrowsMid_A.PushBack({ 896, 0, 128, 275 });
	anim_ArrowsMid_A.speed = 0.3f;
	anim_ArrowsMid_A.loop;
}
