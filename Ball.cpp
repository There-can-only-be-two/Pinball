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

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(ball->body->GetTransform().p.x);
	position.y = METERS_TO_PIXELS(ball->body->GetTransform().p.y);

	SDL_Rect rect = { position.x, position.y, 31, 29 };
	App->renderer->Blit(texture, 139, 187, &rect);


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