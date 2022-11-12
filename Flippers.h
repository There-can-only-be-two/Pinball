#pragma once
#include "Module.h"

#include "Globals.h"
#include "p2Point.h"
#include "Entity.h"
#include "Box2D/Box2D/Box2D.h"
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

public:
	PhysBody* flipperLeft = nullptr;
	PhysBody* flipperRight = nullptr;
	PhysBody* sqr1 = nullptr;

	b2RevoluteJoint* joint1;
private:
	SDL_Texture* texture = nullptr;
	const char* texturePath;	
};