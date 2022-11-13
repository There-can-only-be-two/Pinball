#include "PolyBounce.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleScene.h"

PolyBounce::PolyBounce(Application* app) : Entity(type, app)
{
	name.Create("PolyBounce");
	this->app = app;
}

PolyBounce::~PolyBounce()
{}

// Load assets
bool PolyBounce::Start()
{
	LOG("Loading PolyBounce");

	polyBody = app->physics->CreateCircle(300, 300, 15);
	polyBody->body->SetType(b2_dynamicBody);
	polyBody->ctype = ColliderType::BALL;
	//app->scene_intro->boxes.add(ballBody);
	polyBody->listener = this;
	texture = app->textures->Load("pinball/assets.png");

	return true;
}


// Unload assets
bool PolyBounce::CleanUp()
{
	LOG("Unloading PolyBounce");

	return true;
}

// Update: draw background
bool PolyBounce::Update()
{

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(polyBody->body->GetTransform().p.x - 15);
	position.y = METERS_TO_PIXELS(polyBody->body->GetTransform().p.y - 15);

	SDL_Rect rect = { 229, 106, 31, 31 };
	app->renderer->Blit(texture, position.x, position.y, &rect);


	return true;
}

void PolyBounce::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}