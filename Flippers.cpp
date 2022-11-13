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
	LOG("Loading flippers");
	int fLeft[8] =
	{
		171, 697,
		237, 748,
		231, 756,
		160, 721
	};

	flipperLeft = app->physics->CreateChain(0, 0, fLeft, 8);
	//flipperLeft->body->SetType(b2_staticBody);

	//App->scene_intro->boxes.add(flipperLeft);
	//flipperLeft->listener = this;
	flipperLeft->ctype = ColliderType::FLIPPERS;

	sqr1 = app->physics->CreateRectangle(171, 697, 10, 10);
	sqr1->body->SetType(b2_staticBody);
	app->scene_intro->boxes.add(sqr1);

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = sqr1->body;
	revoluteJointDef.bodyB = flipperLeft->body;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(5), PIXEL_TO_METERS(5));	//the top right corner of the box
	revoluteJointDef.localAnchorB.Set(PIXEL_TO_METERS(5), PIXEL_TO_METERS(0));	//center of the circle

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.referenceAngle = 0;
	revoluteJointDef.lowerAngle = -40 * DEGTORAD;
	revoluteJointDef.upperAngle = 26 * DEGTORAD;
	joint1 = (b2RevoluteJoint*)app->physics->world->CreateJoint(&revoluteJointDef);
		
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

