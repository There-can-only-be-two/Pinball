#include "ModuleLights.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleDebug.h"
#include "ModuleAudio.h"
#include "Flippers.h"
#include "Ball.h"
#include "ModuleFonts.h"

ModuleLights::ModuleLights(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleLights::~ModuleLights() {}

bool ModuleLights::Start()
{
	arrows_left = App->textures->Load("pinball/Lights/arrows_left.png");
	arrows_mid = App->textures->Load("pinball/Lights/arrows_mid.png");
	combo_A = App->textures->Load("pinball/Lights/combo_A.png");
	trigger = App->textures->Load("pinball/Lights/trigger.png");
	x10 = App->textures->Load("pinball/Lights/x10.png");

	return true;
}

update_status ModuleLights::Update()
{
	if (App->debug->lightsON)
	{
		arrows_left_ON = true;
		arrows_mid_ON = true;
		combo_right_ON = true;
		trigger_ON = true;
		x10_ON = true;
	}
	else
	{
		arrows_left_ON = false;
		arrows_mid_ON = false;
		combo_right_ON = false;
		trigger_ON = false;
		x10_ON = false;
	}
	
	return UPDATE_CONTINUE;
}

update_status ModuleLights::PostUpdate()
{
	if (arrows_left_ON)
	{
		SDL_Rect rect = { 0, 0, 128, 275 };
		App->renderer->Blit(arrows_left, 31, 99, &rect);
	}
	else
	{
		SDL_Rect rect = { 128, 0, 128, 275 };
		App->renderer->Blit(arrows_left, 31, 99, &rect);
	}

	if (arrows_mid_ON)
	{
		SDL_Rect rect = { 0, 0, 48, 148 };
		App->renderer->Blit(arrows_mid, 231, 522, &rect);
	}
	else
	{
		SDL_Rect rect = { 48, 0, 48, 148 };
		App->renderer->Blit(arrows_mid, 231, 522, &rect);
	}
	

	//COMBO A
	SDL_Rect rect = { 0, 0, 27, 100 };
	App->renderer->Blit(combo_A, 426, 228, &rect);

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

	}

	return UPDATE_CONTINUE;
}

bool ModuleLights::CleanUp()
{
	App->textures->Unload(arrows_left);
	App->textures->Unload(arrows_mid);
	App->textures->Unload(combo_A);
	App->textures->Unload(trigger);
	App->textures->Unload(x10);
	return true;
}