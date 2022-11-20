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

	texture = app->textures->Load("pinball/assets.png");

	//FLIPPER LEFT
	flipperLeft = app->physics->CreateRectangle(171, 697, 88, 32);

	b2RevoluteJointDef revoluteJointDef1;
	revoluteJointDef1.bodyA = app->scene_intro->platformLeft->body;
	revoluteJointDef1.bodyB = flipperLeft->body;
	revoluteJointDef1.collideConnected = false;
	revoluteJointDef1.localAnchorA.Set(PIXEL_TO_METERS(170), PIXEL_TO_METERS(714));
	revoluteJointDef1.localAnchorB.Set(PIXEL_TO_METERS(-30), PIXEL_TO_METERS(0));

	revoluteJointDef1.enableMotor = false;
	revoluteJointDef1.motorSpeed = 1000.0;
	revoluteJointDef1.maxMotorTorque = 10.0f;

	revoluteJointDef1.enableLimit = true;
	revoluteJointDef1.referenceAngle = 10 * DEGTORAD;
	revoluteJointDef1.lowerAngle = -45 * DEGTORAD;
	revoluteJointDef1.upperAngle = 25 * DEGTORAD;

	joint1 = (b2RevoluteJoint*)app->physics->world->CreateJoint(&revoluteJointDef1);

	// FLIPPER RIGHT
	flipperRight = app->physics->CreateRectangle(360, 697, 88, 32);

	b2RevoluteJointDef revoluteJointDef2;
	revoluteJointDef2.bodyA = app->scene_intro->platformRight->body;
	revoluteJointDef2.bodyB = flipperRight->body;
	revoluteJointDef2.collideConnected = false;
	revoluteJointDef2.localAnchorA.Set(PIXEL_TO_METERS(342), PIXEL_TO_METERS(716));
	revoluteJointDef2.localAnchorB.Set(PIXEL_TO_METERS(30), PIXEL_TO_METERS(0));

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
	delete flipperLeft;
	flipperLeft = nullptr;

	delete flipperRight;
	flipperRight = nullptr;

	return true;
}

// Update: draw background
bool Flippers::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipperLeft_up = true;
		flipperLeft->body->SetAngularVelocity(-1500 * DEGTORAD);
		LOG("%f", flipperLeft->GetRotation());
	}
	else
	{
		flipperLeft->body->SetAngularVelocity(1500 * DEGTORAD);
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipperRight->body->SetAngularVelocity(1500 * DEGTORAD);
		LOG("%f", flipperRight->GetRotation());
	}
	else
	{
		flipperRight->body->SetAngularVelocity(-1500 * DEGTORAD);
	}


	//SFX
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		app->audio->PlayFx(app->scene_intro->sfx_flipper_up);
	else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		app->audio->PlayFx(app->scene_intro->sfx_flipper_down);

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		app->audio->PlayFx(app->scene_intro->sfx_flipper_up);
	else if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		app->audio->PlayFx(app->scene_intro->sfx_flipper_down);


	SDL_Rect rectL = { 6, 94, 92, 35 };
	app->renderer->Blit(texture, METERS_TO_PIXELS(flipperLeft->body->GetPosition().x) - 44, METERS_TO_PIXELS(flipperLeft->body->GetPosition().y) - 18, &rectL, 10.0f, flipperLeft->GetRotation(), 46, 15);

	SDL_Rect rectR = { 105, 94, 92, 35 };
	app->renderer->Blit(texture, METERS_TO_PIXELS(flipperRight->body->GetPosition().x) - 48, METERS_TO_PIXELS(flipperRight->body->GetPosition().y) - 18, &rectR, 10.0f, flipperRight->GetRotation(), 46, 15);

	return true;
}