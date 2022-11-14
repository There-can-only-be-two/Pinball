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
#include "Module.h"

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
	p.x = 500; 
	p.y = 726;
	ballBody = app->physics->CreateCircle(p.x, p.y, 15);
	ballBody->body->SetType(b2_dynamicBody);
	ballBody->ctype = ColliderType::BALL;
	//app->scene_intro->boxes.add(ballBody);
	ballBody->listener = this;
	texture = app->textures->Load("pinball/assets.png");
	
	bounce = false;
	bounceDir = { 0.0f, 0.0f };
	intensity = 0;

	springForce = 0;
	scorex10finished = 0;
	separed = false;
	jointCreated = false;
	

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
	if (bounce) {
		bounceDir.Normalize();
		ballBody->body->ApplyForce(intensity*bounceDir, ballBody->body->GetWorldCenter(), true);
		bounce = false;
	}

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(ballBody->body->GetTransform().p.x - 15);
	position.y = METERS_TO_PIXELS(ballBody->body->GetTransform().p.y - 15);

	SDL_Rect rect = { 229, 106, 31, 31 };
	app->renderer->Blit(texture, position.x, position.y, &rect);

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && app->scene_intro->springSensed && springForce < 400 )
	{
		springForce += 3.0;
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP && app->scene_intro->springSensed && springForce > 30)
	{
		ballBody->body->ApplyForceToCenter(b2Vec2(0, -springForce), true);
		springForce = 0;
		app->scene_intro->springSensed = false;
		LOG("RELEASE BALL");
	}

	if (app->scene_intro->scorex10sensed)
	{
		ballBody->body->ApplyForce(b2Vec2(100, -100), ballBody->body->GetWorldCenter(), true);
		scorex10finished++;
	}
	if (scorex10finished > 300)
	{
		ballBody->body->ApplyForce(b2Vec2(-500, 300), ballBody->body->GetWorldCenter(), true);
		scorex10finished = 0;
		app->scene_intro->scorex10sensed = false;
	}
	
	if (app->scene_intro->ballsensed)
	{
		
		ballBody->body->SetTransform(PIXEL_TO_METERS(p), 0);
		

		app->scene_intro->ballsCounter--;
		app->scene_intro->ballsensed = false;
	}

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
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->blue->body->GetWorldCenter() };
		app->audio->PlayFx(app->scene_intro->bouncer_circle);
		bounce = true;
		intensity = 70;
		break;

	case ColliderType::YELLOW_50:
		LOG("Collision YELLOW_50");
		app->scene_intro->currentScore += 50;
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->yellow->body->GetWorldCenter() };
		app->audio->PlayFx(app->scene_intro->bouncer_circle);
		bounce = true;
		intensity = 70;
		break;

	case ColliderType::RED_100:
		LOG("Collision RED_100");
		app->scene_intro->currentScore += 100;
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->red->body->GetWorldCenter() };
		app->audio->PlayFx(app->scene_intro->bouncer_circle);
		intensity = 70;
		bounce = true;
		break;

	case ColliderType::DIAMOND:
		LOG("Collision DIAMOND");
		break;

	case ColliderType::TRIANGLEL:
		LOG("Collision TRIANGLE");
		app->audio->PlayFx(app->scene_intro->bouncer_tri_1);
		app->audio->PlayFx(app->scene_intro->bouncer_tri_2);
		app->scene_intro->sensorTriLeftSensed = true;
		bounceDir = { 1.0f, -0.5f };
		intensity = 150;
		bounce = true;
		break;

	case ColliderType::TRIANGLER:
		LOG("Collision TRIANGLE");
		app->audio->PlayFx(app->scene_intro->bouncer_tri_1);
		app->audio->PlayFx(app->scene_intro->bouncer_tri_2);
		app->scene_intro->sensorTriRightSensed = true;
		bounceDir = { -1.0f, -0.5f };
		intensity = 150;
		bounce = true;
		break;

	case ColliderType::FRANKFURTL:
		LOG("Collision FRANKFURT");
		break;

	case ColliderType::FRANKFURTR:
		LOG("Collision FRANKFURT");
		break;

	case ColliderType::SPRING_SENSOR:
		LOG("Collision SPRING_SENSOR");
		app->scene_intro->springSensed = true;
		break;

	case ColliderType::SCORE_X10:
		LOG("Collision SCOREX10");
		app->scene_intro->scorex10sensed = true;
		app->audio->PlayFx(app->scene_intro->intro);
		break;

	case ColliderType::BALL_SENSOR:
		LOG("Collision BALL_SENSOR");
		app->scene_intro->ballsensed = true;
		break;

	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}