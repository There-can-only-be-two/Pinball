#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWin.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFadeToBlack.h"

ModuleWin::ModuleWin(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	
}

ModuleWin::~ModuleWin()
{
	// You should do some memory cleaning here, if required
}

bool ModuleWin::Start()
{
	LOG("Loading Win assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	img = App->textures->Load("pinball/win.png");


	return ret;
}

bool ModuleWin::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(img);
	return true;
}

update_status ModuleWin::Update()
{
	App->renderer->Blit(img, 0, 0);
	// If user presses SPACE, enable RayCast
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeBlack(this, (Module*)App->title, 90);
	}

	// Keep playing
	return UPDATE_CONTINUE;
}

