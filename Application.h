#pragma once

#include "p2List.h"
#include "Globals.h"

class Module;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFonts;
class ModulePlayer;
class ModuleScene;
class EntityManager;
class ModulePhysics;
class ModuleFadeToBlack;
class ModuleTitle;
class ModuleWin;
class ModuleDeath;
class ModuleDebug;
class ModuleRender;


class Application
{
public:
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFonts* fonts;
	ModulePlayer* player;

	ModuleScene* scene_intro;
	EntityManager* entityManager;
	ModulePhysics* physics;
	ModuleFadeToBlack* fade;
	ModuleTitle* title;
	ModuleWin* win;
	ModuleDeath* death;
	ModuleDebug* debug;
	ModuleRender* renderer;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};