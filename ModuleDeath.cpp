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
	//ranking.

	
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
	
	score = App->scene_intro->currentScore;

	
	
	return ret;
}

bool ModuleDeath::CleanUp()
{
	LOG("Unloading Death scene");
	App->textures->Unload(img);
	
	App->fonts->UnLoad(font);
	
	// Ranking text
	ofstream myfile;
	myfile.open("RANKING.txt");
	for (int i = 0; i < 5; i++) {
		myfile << ranking[i].name.GetString() << ", " << ranking[i].score << ";\n";
	}
	
	myfile.close();

	return true;
}

update_status ModuleDeath::Update()
{
	App->renderer->Blit(img, 0, 0);
	App->fonts->BlitText(422, 75, font, "RANKING");
	
	char scoreFont[10] = { "\0" };
	

	for (int i = 0; i < 5; i++) {
		App->fonts->BlitText(310, 150*(i+1), font, ranking[i].name.GetString());
		sprintf_s(scoreFont, 10, "%7d", ranking[i].score);
		App->fonts->BlitText(520, 150 * (i + 1), font, scoreFont);
	}

	// If user presses SPACE, enable RayCast
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeBlack(this, (Module*)App->title, 90);
	}

	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleDeath::SwapRank(Scores l[]) {
	int temp_score;
	SString	temp_name;
	for (int i = 0; i < 4; i++) {
		if (l[i].score< l[i+1].score) {
			//Swap scores
			temp_score = l[i].score;
			l[i].score = l[i + 1].score;
			l[i + 1].score = temp_score;

			//Swap names
			temp_name = l[i].name;
			l[i].name = l[i + 1].name;
			l[i + 1].name = temp_name;
			i = -1;
		}
		else {
			continue;
		}
	}
}