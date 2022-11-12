#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Entity.h"
#include "SDL/include/SDL.h"

class Flippers : public Entity	
{
public:
	Flippers();
	virtual ~Flippers();

	bool Start();
	bool Update();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

private:
	SDL_Texture* texture;
	const char* texturePath;

	PhysBody* pbody;
};