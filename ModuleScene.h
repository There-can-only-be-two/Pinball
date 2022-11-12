#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleScene : public Module
{
public:

	// Constructors & Destructors
	ModuleScene(Application* app, bool start_enabled);
	~ModuleScene();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();

	void CreateColliders();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	// Lists of physics objects
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	
	//Map
	PhysBody* bg;
	PhysBody* wallLeft;
	PhysBody* wallRight;
	PhysBody* ball;
	PhysBody* flipperLeft;
	PhysBody* flipperRight;


	// Lower ground sensor (will kill all objects passig through it)
	PhysBody* lower_ground_sensor;
	bool sensed;

	// Textures
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* img;

	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};
