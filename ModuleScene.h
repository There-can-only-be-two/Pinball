#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Entity.h"

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
	void DeleteMap();
public:

	// Lists of physics objects
	p2List<PhysBody*> entityList;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> circles;
	p2List<PhysBody*> ricks;
	
	//Map
	PhysBody* bg;
	PhysBody* wallLeft;
	PhysBody* platformLeft;
	PhysBody* platformRight;
	PhysBody* ballBody;
	
	// Bounce
	PhysBody* diamond;
	PhysBody* triangle_left;
	PhysBody* triangle_right;
	PhysBody* frankfurt_left;
	PhysBody* frankfurt_right;
	PhysBody* blue;
	PhysBody* yellow;
	PhysBody* red;
	/*PhysBody* flipperLeft;
	PhysBody* flipperRight;*/

	//Entities
	Entity* flipperL;
	//Entity* flipperR;
	Entity* ball;

	// Lower ground sensor (will kill all objects passig through it)
	PhysBody* lower_ground_sensor;
	bool sensed;

	// Textures
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* img;


	//scores
	int font;
	char high[10] = { "\0" };
	uint highScore = 0;
	char current[10] = { "\0" };
	uint currentScore = 0;
	char previous[10] = { "\0" };
	uint previousScore = 0;

	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};
