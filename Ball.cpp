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
	p.x = 515; 
	p.y = 726;
	ballBody = app->physics->CreateCircle(p.x, p.y, 15);
	ballBody->body->SetType(b2_dynamicBody);
	ballBody->ctype = ColliderType::BALL;
	//app->scene_intro->boxes.add(ballBody);
	ballBody->listener = this;
	
	bounce = false;
	bounceDir = { 0.0f, 0.0f };
	intensity = 100;

	separed = false;
	jointCreated = false;
	
	scorex10finished = 0;
	delayNewBall = -1;
	delaySaverLeft = -1;
	delaySaverRight = -1;

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
	//Need to Apply Restitution Coefficient !!!
	if (bounce) {
		bounceDir.Normalize();
		ballBody->body->ApplyForce(intensity*bounceDir, ballBody->body->GetWorldCenter(), true);
		bounce = false;
	}

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(ballBody->body->GetTransform().p.x - 15);
	position.y = METERS_TO_PIXELS(ballBody->body->GetTransform().p.y - 15);

	//Spring force
	int springForce = app->scene_intro->springForce;
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		app->scene_intro->springForce = springForce == 420 ? 420 : springForce += 4.0;
	}
	else if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP && app->scene_intro->sensorSpring_Sensed && springForce > 60)
	{
		app->audio->PlayFx(app->scene_intro->sfx_spring);
		ballBody->body->ApplyForceToCenter(b2Vec2(0, -springForce), true);
		app->scene_intro->springForce = 0;
		app->scene_intro->sensorSpring_Sensed = false;
		LOG("RELEASE BALL");
	}
	else
		app->scene_intro->springForce = 0;

	// Gravity
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		app->physics->gravity+=0.5;
		app->physics->world->SetGravity(b2Vec2(GRAVITY_X, app->physics->gravity));
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		app->physics->gravity -= 0.5;
		app->physics->world->SetGravity(b2Vec2(GRAVITY_X, app->physics->gravity));
	}

	// Bounce
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		intensity += 10;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		intensity -= 10;
		
	}

	//Right hole combo
	if (app->scene_intro->sensorX10_Sensed)
	{
		ballBody->body->ApplyForce(b2Vec2(100, -100), ballBody->body->GetWorldCenter(), true);
		scorex10finished++;
	}
	if (scorex10finished > 300)
	{
		ballBody->body->ApplyForce(b2Vec2(-500, 300), ballBody->body->GetWorldCenter(), true);
		scorex10finished = 0;
		app->scene_intro->sensorX10_Sensed = false;
	}
	
	//Delay New Ball
	if (delayNewBall > 0)
		delayNewBall--;
	else if (delayNewBall == 0)
	{
		ballBody->body->SetTransform(PIXEL_TO_METERS(p), 0);
		app->scene_intro->ballsCounter--;
		delayNewBall--;

		if (app->scene_intro->ballsCounter > 0)
			app->audio->PlayFx(app->scene_intro->sfx_new_ball);
	}

	//Delay Saver Left
	if (delaySaverLeft > 0)
		delaySaverLeft--;
	else if (delaySaverLeft == 0)
	{
		ballBody->body->ApplyForceToCenter(b2Vec2(0, -420), true);
		app->audio->PlayFx(app->scene_intro->sfx_spring);
		delete app->scene_intro->saverLeft;
		app->scene_intro->saverLeft = nullptr;
		delaySaverLeft = -255;
	}

	//Delay Saver Right
	if (delaySaverRight > 0)
		delaySaverRight--;
	else if (delaySaverRight == 0)
	{
		ballBody->body->ApplyForceToCenter(b2Vec2(0, -348), true);
		app->audio->PlayFx(app->scene_intro->sfx_spring);
		delete app->scene_intro->saverRight;
		app->scene_intro->saverRight = nullptr;
		delaySaverRight = -255;
	}

	
	return true;
}

bool Ball::PostUpdate()
{
	SDL_Rect rectBall = { 229, 106, 31, 31 };
	app->renderer->Blit(app->scene_intro->assets, position.x, position.y, &rectBall);

	SDL_Rect rectTop = { 0, 0, 115, 335 };
	app->renderer->Blit(app->scene_intro->top, 434, 122, &rectTop);

	//Left saver
	SDL_Rect leftSaver;
	if (delaySaverLeft == -255)
		leftSaver = { 0, 0, 52, 20 };
	else
		leftSaver = { 0, 20, 52, 20 };
	app->renderer->Blit(app->scene_intro->savers, 9, 630, &leftSaver);

	//Right Savers
	SDL_Rect rightSaver;
	if (delaySaverRight == -255)
		rightSaver = { 52, 0, 52, 20 };
	else
		rightSaver = { 52, 20, 52, 20 };
	app->renderer->Blit(app->scene_intro->savers, 450, 630, &rightSaver);

	//Lower part where game info is
	SDL_Rect rectLower = { 0, 0, 462, 207 };
	app->renderer->Blit(app->scene_intro->lower, 24, 730, &rectLower);

	//Time bar
	SDL_Rect bar = { 71, 865, app->scene_intro->time * 0.066666f, 60 };
	app->renderer->DrawQuad(bar, 119 + (3600 - app->scene_intro->time) * 0.027777f, 40 + app->scene_intro->time * 0.045f, app->scene_intro->time * 0.066666f, 255, true);
	SDL_Rect timerRect = { 0, 0, 282, 65 };
	app->renderer->Blit(app->scene_intro->timebar, 50, 860, &timerRect);

	return true;
}

void Ball::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	switch (bodyB->ctype)
	{
	case ColliderType::WALL:
		LOG("Collision WALL");
		break;

	case ColliderType::BLUE_25:
		LOG("Collision BLUE_25");
		app->scene_intro->sensorBlue_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_bouncer_circle);
		app->scene_intro->currentScore += app->scene_intro->AddScore(25);
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->blue->body->GetWorldCenter() };
		bounce = true;
		
		break;

	case ColliderType::YELLOW_50:
		LOG("Collision YELLOW_50");
		app->scene_intro->sensorYellow_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_bouncer_circle);
		app->scene_intro->currentScore += app->scene_intro->AddScore(50);
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->yellow->body->GetWorldCenter() };
		bounce = true;
		
		break;

	case ColliderType::RED_100:
		LOG("Collision RED_100");
		app->scene_intro->sensorRed_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_bouncer_circle);
		app->scene_intro->currentScore += app->scene_intro->AddScore(100);
		bounceDir = { ballBody->body->GetWorldCenter() - app->scene_intro->red->body->GetWorldCenter() };
		bounce = true;
		
		break;

	case ColliderType::SENSOR_TRI_LEFT:
		LOG("Collision TRIANGLE_LEFT");
		app->scene_intro->sensorTriLeft_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_bouncer_tri);
		app->scene_intro->currentScore += app->scene_intro->AddScore(10);
		bounceDir = { 1.0f, -0.5f };
		bounce = true;
		break;

	case ColliderType::SENSOR_TRI_RIGHT:
		LOG("Collision TRIANGLE_RIGHT");
		app->scene_intro->sensorTriRight_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_bouncer_tri);
		app->scene_intro->currentScore += app->scene_intro->AddScore(10);
		bounceDir = { -1.0f, -0.5f };
		
		bounce = true;
		break;



		// SENSORS ===================================================
	case ColliderType::SENSOR_SPRING:
		LOG("Collision SPRING_SENSOR");
		app->scene_intro->sensorSpring_Sensed = true;
		break;

	case ColliderType::SENSOR_X10:
		LOG("Collision SCOREX10");
		app->scene_intro->sensorX10_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_intro);
		app->scene_intro->currentScore += app->scene_intro->AddScore(15000);
		break;

	case ColliderType::SENSOR_DEATH:
		LOG("Collision DEATH");
		if (!app->scene_intro->ray_on && delayNewBall == -1)
		{
			app->audio->PlayFx(app->scene_intro->sfx_death);
			delayNewBall = 100;
			app->scene_intro->sensorDeath_Sensed = true;
			app->scene_intro->scoreMultiplier = 1;
		}
		break;
	
	case ColliderType::SENSOR_COMBO_A1:
		app->scene_intro->sensorComboA1_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_comboA, 0);
		app->scene_intro->currentScore += app->scene_intro->AddScore(200);

		break;

	case ColliderType::SENSOR_COMBO_A2:
		app->scene_intro->sensorComboA2_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_comboA, 0);
		app->scene_intro->currentScore += app->scene_intro->AddScore(200);
		break;

	case ColliderType::SENSOR_COMBO_A3:
		app->scene_intro->sensorComboA3_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_comboA, 0);
		app->scene_intro->currentScore += app->scene_intro->AddScore(200);
		break;

	case ColliderType::SENSOR_COMBO_B1:
		app->scene_intro->sensorComboB1_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_trigger, 0);
		app->scene_intro->currentScore += app->scene_intro->AddScore(300);
		break;

	case ColliderType::SENSOR_COMBO_B2:
		app->scene_intro->sensorComboB2_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_trigger, 0);
		app->scene_intro->currentScore += app->scene_intro->AddScore(300);
		break;

	case ColliderType::SENSOR_COMBO_B3:
		app->scene_intro->sensorComboB3_Sensed = true;
		app->audio->PlayFx(app->scene_intro->sfx_trigger, 0);
		app->scene_intro->currentScore += app->scene_intro->AddScore(300);
		break;
		
	case ColliderType::SENSOR_TIME:
		app->scene_intro->sensorTime_Sensed = true;
		app->scene_intro->scoreMultiplier = 0;
		app->scene_intro->time += app->scene_intro->timeScore*0.06;
		app->scene_intro->timeScore = 0;

		break;

	case ColliderType::SAVER_LEFT:
		delaySaverLeft = 100;
		app->scene_intro->saverLeftSensed = true;

		break;

	case ColliderType::SAVER_RIGHT:
		delaySaverRight = 100;
		app->scene_intro->saverRightSensed = true;

		break;

	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}