#include "Globals.h"
#include <iostream>
#include <fstream>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleDeath.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleScene.h"

ModuleDeath::ModuleDeath(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer

}

ModuleDeath::~ModuleDeath()
{
	// You should do some memory cleaning here, if required
}

bool ModuleDeath::Start()
{
	LOG("Loading Death assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	img = App->textures->Load("pinball/title1.png");
	const char fontText[] = "ABCDEFGHIJKLNOPQRSTUVXYZ0123456789:!? ";
	font = App->fonts->Load("pinball/Fonts/black.png", fontText, 1);
	
	// Ranking text
	ofstream myfile;
	myfile.open("RANKING.txt");
	myfile << "YOU: " << App->scene_intro->highScore << "\n";
	myfile.close();
	return ret;
}

bool ModuleDeath::CleanUp()
{
	LOG("Unloading Death scene");
	App->textures->Unload(img);
	return true;
}

update_status ModuleDeath::Update()
{
	App->renderer->Blit(img, 0, 0);
	App->fonts->BlitText(420, 75, font, "RANKING");

	// If user presses SPACE, enable RayCast
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeBlack(this, (Module*)App->title, 90);
	}

	// Keep playing
	return UPDATE_CONTINUE;
}