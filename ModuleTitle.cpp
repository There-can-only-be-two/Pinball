#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTitle.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
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

	timer = 140;
	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	logo = App->textures->Load("pinball/logo.png");

	//Load sound
	sfx_saberON_1 = App->audio->LoadFx("pinball/Audio/saberON_1.wav");
	sfx_saberON_2 = App->audio->LoadFx("pinball/Audio/saberON_2.wav");
	Mix_Volume(-1, 32);

	//Logo sound
	srand(time(NULL));
	int randomInt = rand() % 2;
	if (randomInt == 0)
		App->audio->PlayFx(sfx_saberON_1);
	else
		App->audio->PlayFx(sfx_saberON_2);

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
	App->fonts->BlitText(320, 210, App->fonts->red, "THERE CAN ONLY");
	App->fonts->BlitText(430, 590, App->fonts->red, "BE TWO");

	


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