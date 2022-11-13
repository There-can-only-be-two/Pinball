#include "CircleBounce.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleScene.h"

CircleBounce::CircleBounce(Application* app) : Entity(type, app)
{
	name.Create("CircleBounce");
	this->app = app;
}

CircleBounce::~CircleBounce()
{}

// Load assets
bool CircleBounce::Start()
{
	LOG("Loading CircleBounce");

	circleBody = app->physics->CreateCircle(300, 300, 35);
	circleBody->body->SetType(b2_dynamicBody);
	circleBody->ctype = ColliderType::BALL;
	//app->scene_intro->boxes.add(ballBody);
	circleBody->listener = this;
	texture = app->textures->Load("pinball/assets.png");

	return true;
}


// Unload assets
bool CircleBounce::CleanUp()
{
	LOG("Unloading CircleBounce");

	return true;
}

// Update: draw background
bool CircleBounce::Update()
{

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(circleBody->body->GetTransform().p.x - 15);
	position.y = METERS_TO_PIXELS(circleBody->body->GetTransform().p.y - 15);

	SDL_Rect rect = { 92, 3, 77, 77 };
	app->renderer->Blit(texture, position.x, position.y, &rect);


	return true;
}

void CircleBounce::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}