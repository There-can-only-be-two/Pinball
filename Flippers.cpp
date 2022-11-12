#include "Globals.h"
#include "Application.h"
#include "Flippers.h"

Flippers::Flippers() : Entity(EntityType::FLIPPERS)
{
	name.Create("Flippers");
}

Flippers::~Flippers()
{}

// Load assets
bool Flippers::Start()
{
	LOG("Loading player");
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
	return true;
}

void Flippers::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
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

