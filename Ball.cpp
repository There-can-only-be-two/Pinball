#include "Ball.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleScene.h"

Ball::Ball(Application* app) : Entity(EntityType::BALL, app)
{
	name.Create("Ball");
	this->app = app;
}

Ball::~Ball()
{}

// Load assets
bool Ball::Start()
{
	LOG("Loading player");

	ballBody = app->physics->CreateCircle(300, 300, 15);
	ballBody->body->SetType(b2_dynamicBody);
	ballBody->ctype = ColliderType::BALL;
	//app->scene_intro->boxes.add(ballBody);
	ballBody->listener = this;
	texture = app->textures->Load("pinball/assets.png");

	return true;
}


// Unload assets
bool Ball::CleanUp()
{
	LOG("Unloading player");
	delete ballBody;
	ballBody = nullptr;
	return true;
}

// Update: draw background
bool Ball::Update()
{

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(ballBody->body->GetTransform().p.x - 15);
	position.y = METERS_TO_PIXELS(ballBody->body->GetTransform().p.y - 15);

	SDL_Rect rect = { 229, 106, 31, 31 };
	app->renderer->Blit(texture, position.x, position.y, &rect);


	return true;
}

void Ball::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	switch (bodyB->ctype)
	{
	case ColliderType::FLIPPERS:
		LOG("Collision FLIPPERS");
		break;
	case ColliderType::WALL:
		LOG("Collision WALL");
		break;
	case ColliderType::BLUE_25:
		LOG("Collision BLUE_25");
		app->scene_intro->currentScore += 25;
		ballBody->body->ApplyForce(b2Vec2(position.x-bodyB->body->GetWorldCenter().x, position.y - bodyB->body->GetWorldCenter().y), ballBody->body->GetWorldCenter(), true);
		break;
	case ColliderType::YELLOW_50:
		LOG("Collision YELLOW_50");
		app->scene_intro->currentScore += 50;
		break;
	case ColliderType::RED_100:
		LOG("Collision RED_100");
		app->scene_intro->currentScore += 100;
		break;
	case ColliderType::DIAMOND:
		LOG("Collision DIAMOND");
		break;
	case ColliderType::TRIANGLE:
		LOG("Collision TRIANGLE");
		break;
	case ColliderType::FRANKFURT:
		LOG("Collision FRANKFURT");
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}