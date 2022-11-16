#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene.h"

ModuleTitle::ModuleTitle(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	logo = NULL;

}

ModuleTitle::~ModuleTitle()
{
	// You should do some memory cleaning here, if required
}

bool ModuleTitle::Start()
{
	LOG("Loading Title assets");
	bool ret = true;

	timer = 120;
	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	logo = App->textures->Load("pinball/logo.png");


	return ret;
}

bool ModuleTitle::CleanUp()
{
	LOG("Unloading Title scene");
	App->textures->Unload(logo);
	return true;
}

update_status ModuleTitle::Update()
{
	App->renderer->Blit(logo, 280, 180);
	// If user presses SPACE, enable RayCast
	
	App->audio->PlayFx(App->scene_intro->sfx_bouncer_tri_1);

	// Keep playing
	return UPDATE_CONTINUE;
}

update_status ModuleTitle::PostUpdate()
{
	if (timer == 0 || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
  		App->fade->FadeBlack(this,(Module*)App->scene_intro, 90);
	}
	timer--;

	return UPDATE_CONTINUE;
}