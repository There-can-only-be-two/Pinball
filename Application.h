#pragma once

#include "p2List.h"
#include "Globals.h"

class Module;
class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleSceneIntro;
class EntityManager;
class ModulePhysics;
class ModuleFadeToBlack;
class ModuleTitle;
class ModuleWin;
class ModuleDeath;

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	EntityManager* entityManager;
	ModulePhysics* physics;
	ModuleFadeToBlack* fade;
	ModuleTitle* title;
	ModuleWin* win;
	ModuleDeath* death;

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