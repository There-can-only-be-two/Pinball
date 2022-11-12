#include "Flippers.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "EntityManager.h"


Flippers::Flippers(Application* app) : Entity(EntityType::FLIPPERS, app)
{
	name.Create("Flippers");
	this->app = app;
}

Flippers::~Flippers()
{}

// Load assets
bool Flippers::Start()
{
	LOG("Loading player");

	
	//FLIPPER LEFT
	sqr1 = app->physics->CreateRectangle(150, 705, 20, 20);
	sqr1->body->SetType(b2_staticBody);

	flipperLeft = app->physics->CreateRectangle(171, 697, 90, 30);
	flipperLeft->listener = this;
	flipperLeft->ctype = ColliderType::FLIPPERS;

	b2RevoluteJointDef revoluteJointDef1;
	revoluteJointDef1.bodyA = sqr1->body;
	revoluteJointDef1.bodyB = flipperLeft->body;
	revoluteJointDef1.collideConnected = false;
	revoluteJointDef1.localAnchorA.Set(PIXEL_TO_METERS(5), PIXEL_TO_METERS(5));//the top right corner of the box
	revoluteJointDef1.localAnchorB.Set(PIXEL_TO_METERS(-45), PIXEL_TO_METERS(0));//center of the circle

	revoluteJointDef1.enableMotor = false;
	revoluteJointDef1.motorSpeed = 1000.0;
	revoluteJointDef1.maxMotorTorque = 10.0f;

	revoluteJointDef1.enableLimit = true;
	revoluteJointDef1.referenceAngle = 0;
	revoluteJointDef1.lowerAngle = -45 * DEGTORAD;
	revoluteJointDef1.upperAngle = 25 * DEGTORAD;
	joint1 = (b2RevoluteJoint*)app->physics->world->CreateJoint(&revoluteJointDef1);
		

	// FLIPPER RIGHT
	sqr2 = app->physics->CreateRectangle(360, 705, 20, 20);
	sqr2->body->SetType(b2_staticBody);

	flipperRight = app->physics->CreateRectangle(360, 697, 90, 30);
	flipperRight->listener = this;
	flipperRight->ctype = ColliderType::FLIPPERS;

	b2RevoluteJointDef revoluteJointDef2;
	revoluteJointDef2.bodyA = sqr2->body;
	revoluteJointDef2.bodyB = flipperRight->body;
	revoluteJointDef2.collideConnected = false;
	revoluteJointDef2.localAnchorA.Set(PIXEL_TO_METERS(-5), PIXEL_TO_METERS(5));//the top right corner of the box
	revoluteJointDef2.localAnchorB.Set(PIXEL_TO_METERS(45), PIXEL_TO_METERS(0));//center of the circle

	revoluteJointDef2.enableMotor = false;
	revoluteJointDef2.motorSpeed = 1000.0;
	revoluteJointDef2.maxMotorTorque = 10.0f;

	revoluteJointDef2.enableLimit = true;
	revoluteJointDef2.referenceAngle = 0;
	revoluteJointDef2.lowerAngle = -25 * DEGTORAD;
	revoluteJointDef2.upperAngle = 45 * DEGTORAD;
	joint2 = (b2RevoluteJoint*)app->physics->world->CreateJoint(&revoluteJointDef2);

	return true;
}

// Update: draw background
bool Flippers::Update()
{

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipperLeft->body->SetAngularVelocity(-15.0f);
	}
	else flipperLeft->body->SetAngularVelocity(10.0f);

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipperRight->body->SetAngularVelocity(15.0f);
	}
	else flipperRight->body->SetAngularVelocity(-10.0f);

	return true;
}

// Unload assets
bool Flippers::CleanUp()
{
	LOG("Unloading player");

	return true;
}