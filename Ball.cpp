#include "Ball.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

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

	ballBody = app->physics->CreateCircle(100, 100, 20);
	ballBody->body->SetType(b2_dynamicBody);
	ballBody->ctype = ColliderType::BALL;
	ballBody->listener = this;
	texture = app->textures->Load("pinball/assets.png");

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
	position.x = METERS_TO_PIXELS(ballBody->body->GetTransform().p.x);
	position.y = METERS_TO_PIXELS(ballBody->body->GetTransform().p.y);

	SDL_Rect rect = { position.x, position.y, 31, 29 };
	app->renderer->Blit(texture, 139, 187, &rect);


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