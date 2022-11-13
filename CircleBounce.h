#pragma once
#include "Module.h"

#include "Globals.h"
#include "p2Point.h"
#include "Entity.h"
#include "Box2D/Box2D/Box2D.h"
#include "SDL/include/SDL.h"

class CircleBounce : public Entity {
public:
	CircleBounce(Application* App);
	virtual ~CircleBounce();

	bool Start();
	bool Update();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	PhysBody* circleBody = nullptr;

private:
	SDL_Texture* texture = nullptr;
};
