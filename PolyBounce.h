#pragma once
#include "Module.h"

#include "Globals.h"
#include "p2Point.h"
#include "Entity.h"
#include "Box2D/Box2D/Box2D.h"
#include "SDL/include/SDL.h"

class PolyBounce : public Entity {
public:
	PolyBounce(Application* App);
	virtual ~PolyBounce();

	bool Start();
	bool Update();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	PhysBody* polyBody = nullptr;

private:
	SDL_Texture* texture = nullptr;
};
