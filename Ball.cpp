#include "Ball.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

Ball::Ball() : Entity(EntityType::BALL, App)
{
	name.Create("Ball");
}

Ball::~Ball()
{}

// Load assets
bool Ball::Start()
{
	LOG("Loading player");

	ball = App->physics->CreateCircle(100, 100, 20);
	ball->listener = this;
	texture = App->textures->Load("pinball/assets.png");

	return true;
}


// Unload assets
bool Ball::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
bool Ball::Update()
{


	return true;
}

void Ball::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	/*switch ()
	{
	case ColliderType::WALL:
		LOG("Collision WALL");

		break;
	case ColliderType::FLIPPERS:
		LOG("Collision FLIPPERS");
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}*/
}