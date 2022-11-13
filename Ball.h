#pragma once
#include "Module.h"

#include "Globals.h"
#include "p2Point.h"
#include "Entity.h"
#include "Box2D/Box2D/Box2D.h"
#include "SDL/include/SDL.h"

class Ball : public Entity {
public:
	Ball(Application* App);
	virtual ~Ball();

	bool Start();
	bool Update();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	PhysBody* ballBody = nullptr;

	float springForce;
	
	b2RevoluteJoint* joint;
	int scorex10finished;
	bool separed, jointCreated;

private:
	SDL_Texture* texture = nullptr;
};