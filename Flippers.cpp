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
	
	flipperLeft = app->physics->CreateRectangle(550, 550, 100, 100);
	flipperLeft->body->SetType(b2_staticBody);

	//App->scene_intro->boxes.add(flipperLeft);
	//flipperLeft->listener = this;
	flipperLeft->ctype = ColliderType::FLIPPERS;

	sqr1 = app->physics->CreateRectangle(550, 550, 200, 200);
	sqr1->body->SetType(b2_staticBody);
	app->scene_intro->boxes.add(sqr1);

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = (b2Body*)flipperLeft;
	revoluteJointDef.bodyB = (b2Body*)sqr1;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(50, 50);//the top right corner of the box
	revoluteJointDef.localAnchorB.Set(100, 100);//center of the circle

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.referenceAngle = 0;
	revoluteJointDef.lowerAngle = -45 * DEGTORAD;
	revoluteJointDef.upperAngle = 45 * DEGTORAD;
	//joint1 = (b2RevoluteJoint*)app->physics->world->CreateJoint(&revoluteJointDef);
		
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

