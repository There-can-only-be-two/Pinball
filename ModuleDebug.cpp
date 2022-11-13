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

ModuleDebug::ModuleDebug(Application* app, bool start_enabled) : Module(app, start_enabled) { debug = false; }
ModuleDebug::~ModuleDebug() {}

bool ModuleDebug::Start()
{
	debug = false;
	return true;
}

update_status ModuleDebug::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
		debug = !debug;

	if (debug)
	{
		if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
			variables = !variables;

		if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
			camLimits = !camLimits;

		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			teleport = !teleport;
	}

	// F1/F2: Start from the first/second level
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {

	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {

	}

	// F3: Start from the beginning of the current level
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {

	}

	// F5: Save the current game state
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		//App->SaveGameRequest();
	}

	// F6: Load the previous state (even across levels)
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		//App->LoadGameRequest();
	}

	// F9: View colliders / logic
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		//App->physics->debug = !App->physics->debug;
	}

	// F10: God Mode (fly around, cannot be killed, etc)
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		godMode = !godMode;
	}

	// F11: Free camera
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN) {
		freeCam = !freeCam;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleDebug::PostUpdate()
{
	if (debug)
		DrawDebug();

	return UPDATE_CONTINUE;
}

void ModuleDebug::DrawDebug()
{
	//int scale = App->win->GetScale();

	//int debugX = App->render->camera.w / scale * 0.7;
	//int debugY = App->render->camera.h / scale * 0.1;

	//App->fonts->BlitText(debugX, debugY, 0, "variables (v)");
	////Camera Limits
	//if (camLimits)
	//	App->fonts->BlitText(debugX, debugY + 10, 0, "camera limits (c)  on");
	//else
	//	App->fonts->BlitText(debugX, debugY + 10, 0, "camera limits (c)  off");


	////Variables
	//if (variables)
	//{
	//	//God Mode
	//	if (godMode)
	//		App->fonts->BlitText(debugX, debugY + 30, 0, "#god mode (f10)  on");
	//	else
	//		App->fonts->BlitText(debugX, debugY + 30, 0, "#god mode (f10)  off");

	//	//Free Camera
	//	if (freeCam)
	//		app->fonts->BlitText(debugX, debugY + 40, 0, "#free cam (f11)  on");
	//	else
	//		app->fonts->BlitText(debugX, debugY + 40, 0, "#free cam (f11)  off");

	//	//Player x, y
	//	app->fonts->BlitText(debugX, debugY + 55, 0, "player.x =");
	//	app->fonts->BlitText(debugX + 88, debugY + 55, 0, std::to_string(app->scene->player->position.x).c_str());

	//	app->fonts->BlitText(debugX, debugY + 65, 0, "player.y =");
	//	app->fonts->BlitText(debugX + 88, debugY + 65, 0, std::to_string(app->scene->player->position.y).c_str());

	//	//Camera x, y
	//	app->fonts->BlitText(debugX, debugY + 80, 0, "camera.x =");
	//	app->fonts->BlitText(debugX + 88, debugY + 80, 0, std::to_string(app->render->camera.x).c_str());

	//	app->fonts->BlitText(debugX, debugY + 90, 0, "camera.y =");
	//	app->fonts->BlitText(debugX + 88, debugY + 90, 0, std::to_string(app->render->camera.y).c_str());

	//	//Player alive
	//	if (app->scene->player->alive)
	//		app->fonts->BlitText(debugX, debugY + 105, 0, "player.alive = true");
	//	else
	//		app->fonts->BlitText(debugX, debugY + 105, 0, "player.alive = false");
	//}

	////Camera limits
	//if (camLimits)
	//{
	//	App->scene->rectCamera.x = app->render->camera.w * 0.4;
	//	App->scene->rectCamera.y = app->render->camera.h * 0.4;
	//	App->scene->rectCamera.w = app->render->camera.w * 0.2;
	//	App->scene->rectCamera.h = app->render->camera.h * 0.2;
	//	App->render->DrawRectangle(app->scene->rectCamera, 0, 255, 0, 255, false, false);
	//}

	////Teleport
	//if (teleport)
	//{
	//	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	//	{
	//		app->scene->player->position.x = 2120;
	//		app->scene->player->position.y = 385;
	//	}
	//}
}