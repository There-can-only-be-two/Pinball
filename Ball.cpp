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

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && app->scene_intro->spring_Sensed && springForce < 400 )
	{
		springForce += 3.0;
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP && app->scene_intro->spring_Sensed && springForce > 30)
	{
		ballBody->body->ApplyForceToCenter(b2Vec2(0, -springForce), true);
		springForce = 0;
		app->scene_intro->spring_Sensed = false;
		LOG("RELEASE BALL");
	}

	if (app->scene_intro->scorex10_Sensed)
	{
		ballBody->body->ApplyForce(b2Vec2(100, -100), ballBody->body->GetWorldCenter(), true);
		scorex10finished++;
	}
	if (scorex10finished > 300)
	{
		ballBody->body->ApplyForce(b2Vec2(-500, 300), ballBody->body->GetWorldCenter(), true);
		scorex10finished = 0;
		app->scene_intro->scorex10_Sensed = false;
	}
	
	if (app->scene_intro->ball_Sensed)
	{
		
		ballBody->body->SetTransform(PIXEL_TO_METERS(p), 0);
		

		app->scene_intro->ballsCounter--;
		app->scene_intro->ball_Sensed = false;
	}

	return true;
}

bool Ball::PostUpdate() {
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
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->blue->body->GetWorldCenter() };
		bounce = true;
		intensity = 100;
		break;

	case ColliderType::YELLOW_50:
		LOG("Collision YELLOW_50");
		app->scene_intro->currentScore += 50;
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->yellow->body->GetWorldCenter() };
		bounce = true;
		intensity = 100;
		break;

	case ColliderType::RED_100:
		LOG("Collision RED_100");
		app->scene_intro->currentScore += 100;
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->red->body->GetWorldCenter() };
		bounce = true;
		intensity = 100;	
		break;

	case ColliderType::TRIANGLEL:
		LOG("Collision TRIANGLE");
		app->audio->PlayFx(app->scene_intro->bouncer_tri_1);
		app->audio->PlayFx(app->scene_intro->bouncer_tri_2);
		app->scene_intro->sensorTriLeft_Sensed = true;
		bounceDir = { 1.0f, -0.5f };
		intensity = 180;
		bounce = true;
		break;

	case ColliderType::TRIANGLER:
		LOG("Collision TRIANGLE");
		app->audio->PlayFx(app->scene_intro->bouncer_tri_1);
		app->audio->PlayFx(app->scene_intro->bouncer_tri_2);
		app->scene_intro->sensorTriRight_Sensed = true;
		bounceDir = { -1.0f, -0.5f };
		intensity = 180;
		bounce = true;
		break;

	case ColliderType::FRANKFURTL:
		LOG("Collision FRANKFURT");
		break;

	case ColliderType::FRANKFURTR:
		LOG("Collision FRANKFURT");
		break;


		//SENSORS
	case ColliderType::SPRING_SENSOR:
		LOG("Collision SPRING_SENSOR");
		app->scene_intro->spring_Sensed = true;
		break;

	case ColliderType::SCORE_X10:
		LOG("Collision SCOREX10");
		app->scene_intro->scorex10_Sensed = true;
		app->audio->PlayFx(app->scene_intro->intro);
		break;

	case ColliderType::BALL_SENSOR:
		LOG("Collision BALL_SENSOR");
		if (!app->scene_intro->ray_on)
			app->scene_intro->ball_Sensed = true;
		break;
	
	case ColliderType::SENSOR_COMBO_A1:
		app->scene_intro->sensorComboA1_Sensed = true;
		break;

	case ColliderType::SENSOR_COMBO_A2:
		app->scene_intro->sensorComboA2_Sensed = true;

		break;

	case ColliderType::SENSOR_COMBO_A3:
		app->scene_intro->sensorComboA3_Sensed = true;

		break;

	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}