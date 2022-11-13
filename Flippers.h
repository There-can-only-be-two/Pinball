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
	Flippers(Application* App);
	virtual ~Flippers();

	bool Start();
	bool Update();
	bool CleanUp();

public:

	PhysBody* flipperLeft = nullptr;
	PhysBody* flipperRight = nullptr;

	PhysBody* sqr1 = nullptr;
	PhysBody* sqr2 = nullptr;

	b2RevoluteJoint* joint1 = nullptr;
	b2RevoluteJoint* joint2 = nullptr;

private:
	SDL_Texture* texture = nullptr;
	const char* texturePath;
};