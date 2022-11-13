#include "ModuleDebug.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "Flippers.h"
#include "ModulePhysics.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleDeath.h"
#include "ModuleTitle.h"

#include <string>

ModuleDebug::ModuleDebug(Application* app, bool start_enabled) : Module(app, start_enabled) { drawDebug = false; }
ModuleDebug::~ModuleDebug() {}

bool ModuleDebug::Start()
{
	drawDebug = false;
	return true;
}

update_status ModuleDebug::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
		drawDebug = !drawDebug;

	if (drawDebug)
	{
		if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
			variables = !variables;
	}

	// F9: View colliders / logic
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		App->physics->debug = !App->physics->debug;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleDebug::PostUpdate()
{
	if (drawDebug)
		DrawDebug();

	return UPDATE_CONTINUE;
}

void ModuleDebug::DrawDebug()
{
	int debugX = App->renderer->camera.w * 0.6;
	int debugY = App->renderer->camera.h * 0.1;


	App->fonts->BlitText(debugX, debugY + 300, 0, "#DEBUG MODE (TAB)  ON/OFF");

	//Colliders
	/*if (App->physics->debug)
		App->fonts->BlitText(debugX, debugY + 40, 0, "#COLLIDERS (F1)  ON");
	else
		App->fonts->BlitText(debugX, debugY + 40, 0, "#COLLIDERS (F1)  OFF");*/

	if (variables)
	{
		//Ball x, y
		App->fonts->BlitText(debugX, debugY + 340, 0, "BALL.X : ");		//26, 33
		App->fonts->BlitText(debugX + 234, debugY + 340, 0, std::to_string(App->scene_intro->ball->position.x).c_str());

		App->fonts->BlitText(debugX, debugY + 380, 0, "BALL.Y : ");
		App->fonts->BlitText(debugX + 234, debugY + 380, 0, std::to_string(App->scene_intro->ball->position.y).c_str());




		//Player alive
		/*if (App->scene->player->alive)
			App->fonts->BlitText(debugX, debugY + 105, 0, "player.alive = true");
		else
			App->fonts->BlitText(debugX, debugY + 105, 0, "player.alive = false");*/
	}	
}