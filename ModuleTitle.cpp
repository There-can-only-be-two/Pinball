#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFadeToBlack.h"

ModuleTitle::ModuleTitle(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer

}

ModuleTitle::~ModuleTitle()
{
	// You should do some memory cleaning here, if required
}

bool ModuleTitle::Start()
{
	LOG("Loading Title assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	img = App->textures->Load("pinball/wheel.png");


	return ret;
}

bool ModuleTitle::CleanUp()
{
	LOG("Unloading Title scene");
	App->textures->Unload(img);
	return true;
}

update_status ModuleTitle::Update()
{
	//App->renderer->draw
	// If user presses SPACE, enable RayCast
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
  		App->fade->FadeBlack(this,(Module*)App->scene_intro, 1);
	}

	// Keep playing
	return UPDATE_CONTINUE;
}