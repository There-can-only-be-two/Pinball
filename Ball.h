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
	bool PostUpdate();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	b2Vec2 p;
	PhysBody* ballBody = nullptr;
	b2Vec2 bounceDir;
	bool bounce;
	
	
	b2RevoluteJoint* joint;
	bool separed, jointCreated;

	int scorex10finished;
	int delayNewBall;
	int delaySaverLeft;
	int delaySaverRight;

private:
};