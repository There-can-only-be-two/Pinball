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

	texture = app->textures->Load("pinball/Assets.png");

	//FLIPPER LEFT
	flipperLeft = app->physics->CreateRectangle(171, 697, 90, 30);
	flipperLeft->listener = this;
	flipperLeft->ctype = ColliderType::FLIPPERS;
	b2RevoluteJointDef revoluteJointDef1;
	revoluteJointDef1.bodyA = app->scene_intro->platformLeft->body;
	revoluteJointDef1.bodyB = flipperLeft->body;
	revoluteJointDef1.collideConnected = false;
	revoluteJointDef1.localAnchorA.Set(PIXEL_TO_METERS(152), PIXEL_TO_METERS(712));
	revoluteJointDef1.localAnchorB.Set(PIXEL_TO_METERS(-45), PIXEL_TO_METERS(7.5));

	revoluteJointDef1.enableMotor = false;
	revoluteJointDef1.motorSpeed = 1000.0;
	revoluteJointDef1.maxMotorTorque = 10.0f;

	revoluteJointDef1.enableLimit = true;
	revoluteJointDef1.referenceAngle = 10 * DEGTORAD;
	revoluteJointDef1.lowerAngle = -45 * DEGTORAD;
	revoluteJointDef1.upperAngle = 25 * DEGTORAD;
	joint1 = (b2RevoluteJoint*)app->physics->world->CreateJoint(&revoluteJointDef1);

	// FLIPPER RIGHT
	flipperRight = app->physics->CreateRectangle(360, 697, 90, 30);
	flipperRight->listener = this;
	flipperRight->ctype = ColliderType::FLIPPERS;

	b2RevoluteJointDef revoluteJointDef2;
	revoluteJointDef2.bodyA = app->scene_intro->platformRight->body;
	revoluteJointDef2.bodyB = flipperRight->body;
	revoluteJointDef2.collideConnected = false;
	revoluteJointDef2.localAnchorA.Set(PIXEL_TO_METERS(358), PIXEL_TO_METERS(712));
	revoluteJointDef2.localAnchorB.Set(PIXEL_TO_METERS(45), PIXEL_TO_METERS(7.5));

	revoluteJointDef2.enableMotor = false;
	revoluteJointDef2.motorSpeed = 1000.0;
	revoluteJointDef2.maxMotorTorque = 10.0f;

	revoluteJointDef2.referenceAngle = -10 * DEGTORAD;
	revoluteJointDef2.lowerAngle = -25 * DEGTORAD;
	revoluteJointDef2.upperAngle = 45 * DEGTORAD;
	revoluteJointDef2.enableLimit = true;
	joint2 = (b2RevoluteJoint*)app->physics->world->CreateJoint(&revoluteJointDef2);
		
	return true;
}

// Unload assets
bool Flippers::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
bool Flippers::Update()
{
	double angle;
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipperLeft->body->SetAngularVelocity(-1200.0f * DEGTORAD);
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		flipperLeft->body->SetAngularVelocity(1200.0f * DEGTORAD);
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipperRight->body->SetAngularVelocity(1200.0f * DEGTORAD);
	}
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		flipperRight->body->SetAngularVelocity(-1200.0f * DEGTORAD);
	}
	SDL_Rect rectL = { 4, 86, 86, 60 };
	/*SDL_Point* pointSDL = { 0};
	SDL_RenderCopyEx(app->renderer->renderer, texture, &rectL, (double)flipperLeft->body->GetAngle(), pointSDL*, SDL_FLIP_VERTICAL);*/
	app->renderer->Blit(texture, METERS_TO_PIXELS(flipperLeft->body->GetPosition().x) - 36, METERS_TO_PIXELS(flipperLeft->body->GetPosition().y) - 34, &rectL, 10.0f, (double)(flipperLeft->body->GetAngle() * DEGTORAD));

	SDL_Rect rectR = { 118, 86, 86, 60 };
	app->renderer->Blit(texture, METERS_TO_PIXELS(flipperRight->body->GetPosition().x) - 45, METERS_TO_PIXELS(flipperRight->body->GetPosition().y) - 34, &rectR, 10.0f, (double)(flipperRight->body->GetAngle() * DEGTORAD));

	return true;
}


