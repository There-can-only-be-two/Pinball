#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFadeToBlack.h"
#include "Flippers.h"
#include "Ball.h"
#include "EntityManager.h"
#include "ModuleFonts.h"
#include "ModuleLights.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	circle = box = rick = NULL;
	ray_on = false;
	highScore = 1000;
	currentScore = 0;
	previousScore = 0;
}

ModuleScene::~ModuleScene()
{
	// You should do some memory cleaning here, if required
}

bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	flipperL = (Flippers*)App->entityManager->CreateEntity(EntityType::FLIPPERS);
	ball = (Ball*)App->entityManager->CreateEntity(EntityType::BALL);

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	CreateColliders();
	CreateSensors();


	// Load textures
	//img = App->textures->Load("pinball/pinball_composition.png");
	img = App->textures->Load("pinball/background.png");
	img = App->textures->Load("pinball/top.png");


	//Fonts
	const char fontText[] = "ABCDEFGHIJKLNOPQRSTUVXYZ0123456789:!? ";
	font = App->fonts->Load("pinball/Fonts/white.png", fontText, 1);
	fontHype = App->fonts->Load("pinball/Fonts/yellow.png", fontText, 1);


	//Audio
	Mix_VolumeMusic(10);
	//App->audio->PlayMusic("Assets/Audio/", 0);
	//App->audio->LoadFx("Assets/Audio/");
	intro = App->audio->LoadFx("pinball/Audio/intro.wav");
	flipper = App->audio->LoadFx("pinball/Audio/flipper.wav");
	spring = App->audio->LoadFx("pinball/Audio/spring.wav");
	bouncer_circle = App->audio->LoadFx("pinball/Audio/bouncer_circle.wav");
	bouncer_tri_1 = App->audio->LoadFx("pinball/Audio/bouncer_tri_1.wav");
	bouncer_tri_2 = App->audio->LoadFx("pinball/Audio/bouncer_tri_2.wav");


	//Set variables
	previousScore = currentScore;
	currentScore = 0;

	App->entityManager->Enable();
	App->lights->Enable();


	return ret;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(circle);
	App->textures->Unload(box);
	App->textures->Unload(rick);
	App->textures->Unload(img);
	App->fonts->UnLoad(font);
	DeleteMap();
	
	return true;
}

update_status ModuleScene::Update()
{
	//Draws variables
	sprintf_s(high, 10, "%7d", highScore);
	sprintf_s(current, 10, "%7d", currentScore);
	sprintf_s(previous, 10, "%7d", previousScore);

	App->renderer->Blit(img, 0, 0);
	App->fonts->BlitText(600, 75, font, "HIGHSCORE:");

	App->fonts->BlitText(600, 175, font, "CURRENT SCORE:");

	App->fonts->BlitText(600, 275, font, "PREVIOUS SCORE:");
	App->fonts->BlitText(700, 330, font, previous);

	if (highScore > currentScore) {
		App->fonts->BlitText(700, 130, font, high);		
		App->fonts->BlitText(700, 230, font, current);		
	}
	else {
		highScore = currentScore;
		App->fonts->BlitText(700, 130, fontHype, high);
		App->fonts->BlitText(700, 230, fontHype, current);
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		App->fade->FadeBlack(this, (Module*)App->death, 90);
		App->entityManager->Disable();
	}


	#pragma region RAYCAST
	// Prepare for raycast ------------------------------------------------------
	
	// The target point of the raycast is the mouse current position (will change over game time)
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// Total distance of the raycast reference segment
	int ray_hit = ray.DistanceTo(mouse);

	// Declare a vector. We will draw the normal to the hit surface (if we hit something)
	fVector normal(0.0f, 0.0f);

	// Raycasts -----------------
	if(ray_on == true)
	{
		// Compute the vector from the raycast origin up to the contact point (if we're hitting anything; otherwise this is the reference length)
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		// Draw a line from origin to the hit point (or reference length if we are not hitting anything)
		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		// If we are hitting something with the raycast, draw the normal vector to the contact point
		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}
	#pragma endregion

	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleScene::CreateColliders()
{
	//Map
	int BG[112] =
	{
		491, 240,
		496, 266,
		497, 295,
		497, 806,
		534, 806,
		534, 216,
		523, 186,
		501, 152,
		469, 118,
		424, 83,
		364, 56,
		282, 45,
		204, 54,
		135, 81,
		80, 127,
		51, 164,
		24, 214,
		24, 314,
		31, 361,
		44, 399,
		64, 436,
		79, 456,
		81, 468,
		77, 482,
		60, 500,
		40, 524,
		24, 553,
		24, 753,
		62, 753,
		253, 850,
		449, 751,
		484, 751,
		484, 488,
		469, 464,
		473, 432,//
		461, 418,
		432, 428,
		420, 411,
		418, 393,
		430, 362,
		445, 329,
		450, 312,
		452, 292,
		450, 269,
		444, 247,
		431, 220,
		407, 193,
		370, 163,
		361, 149,
		363, 130,
		379, 122,
		402, 129,
		427, 146,
		447, 165,
		472, 197,
		483, 217
	};
	int WALL_LEFT[64] =
	{
		206, 160,
		180, 178,
		155, 201,
		134, 228,
		122, 254,
		115, 284,
		114, 312,
		116, 338,
		122, 365,
		130, 388,
		142, 412,
		146, 425,
		145, 430,
		140, 433,
		133, 431,
		121, 421,
		108, 402,
		93, 377,
		82, 348,
		76, 311,
		75, 278,
		78, 250,
		87, 220,
		101, 191,
		122, 167,
		144, 146,
		165, 131,
		183, 121,
		195, 120,
		207, 126,
		212, 139,
		212, 151
	};
	int PLATFORM_LEFT[24] =
	{
		58, 650,
		58, 663,
		63, 673,
		149, 717,
		154, 716,
		163, 698,
		162, 692,
		74, 647,
		69, 641,
		67, 635,
		63, 632,
		59, 635
	};
	int PLATFORM_RIGHT[24] =
	{
		452, 650,
		451, 666,
		446, 673,
		361, 717,
		355, 714,
		348, 701,
		348, 692,
		433, 649,
		439, 645,
		444, 634,
		447, 632,
		450, 634
	};


	bg = App->physics->CreateChain(0, 0, BG, 112);
	bg->body->SetType(b2BodyType::b2_staticBody);

	wallLeft = App->physics->CreateChain(0, 0, WALL_LEFT, 64);
	wallLeft->body->SetType(b2BodyType::b2_staticBody);

	platformLeft = App->physics->CreateChain(0, 0, PLATFORM_LEFT, 24);
	platformLeft->body->SetType(b2BodyType::b2_staticBody);

	platformRight = App->physics->CreateChain(0, 0, PLATFORM_RIGHT, 24);
	platformRight->body->SetType(b2BodyType::b2_staticBody);


	// Bounce
	int DIAMOND[34] =
	{
		205, 440,
		246, 420,
		251, 418,
		256, 418,
		261, 418,
		266, 419,
		308, 438,
		313, 442,
		314, 448,
		314, 454,
		309, 460,
		268, 480,
		257, 482,
		247, 480,
		204, 461,
		199, 454,
		199, 445
	};
	diamond = App->physics->CreateChain(0, 0, DIAMOND, 34);
	diamond->body->SetType(b2BodyType::b2_staticBody);
	diamond->ctype = ColliderType::DIAMOND;

	int REBOUND_LEFT[28] =
	{
		107, 529,
		100, 533,
		97, 540,
		97, 603,
		98, 609,
		101, 614,
		145, 639,
		154, 640,
		160, 637,
		165, 632,
		166, 624,
		164, 616,
		123, 534,
		115, 529
	};
	triangle_left = App->physics->CreateChain(0, 0, REBOUND_LEFT, 28);
	triangle_left->body->SetType(b2BodyType::b2_staticBody);
	
	int REBOUND_RIGHT[28] =
	{
		394, 529,
		388, 533,
		383, 540,
		344, 620,
		343, 628,
		347, 636,
		354, 640,
		365, 639,
		404, 618,
		410, 612,
		413, 604,
		413, 540,
		409, 532,
		402, 529
	};
	triangle_right = App->physics->CreateChain(0, 0, REBOUND_RIGHT, 28);
	triangle_right->body->SetType(b2BodyType::b2_staticBody);

	int FRANKFURT_LEFT[24] =
	{
		180, 335,
		203, 379,
		204, 386,
		202, 392,
		195, 397,
		187, 397,
		180, 391,
		159, 349,
		158, 342,
		161, 335,
		167, 331,
		174, 331
	};
	frankfurt_left = App->physics->CreateChain(0, 0, FRANKFURT_LEFT, 24);
	frankfurt_left->body->SetType(b2BodyType::b2_staticBody);
	frankfurt_left->ctype = ColliderType::FRANKFURT;
	
	int FRANKFURT_RIGHT[22] =
	{
		380, 332,
		375, 335,
		352, 380,
		351, 386,
		353, 392,
		358, 396,
		365, 397,
		372, 394,
		397, 347,
		396, 339,
		390, 332
	};
	frankfurt_right = App->physics->CreateChain(0, 0, FRANKFURT_RIGHT, 22);
	frankfurt_right->body->SetType(b2BodyType::b2_staticBody);
	frankfurt_right->ctype = ColliderType::FRANKFURT;

	blue = App->physics->CreateCircle(190+37, 196+39, 25);
	blue->body->SetType(b2BodyType::b2_staticBody);
	blue->ctype = ColliderType::BLUE_25;

	red = App->physics->CreateCircle(300+39, 196 + 39, 25);
	red->body->SetType(b2BodyType::b2_staticBody);
	red->ctype = ColliderType::RED_100;

	yellow = App->physics->CreateCircle(246 + 37, 294 + 37, 25);
	yellow->body->SetType(b2BodyType::b2_staticBody);
	yellow->ctype = ColliderType::YELLOW_50;
}

void ModuleScene::CreateSensors()
{
	springSensor = App->physics->CreateRectangleSensor(515, 800, 10, 10);
	springSensor->ctype = ColliderType::SPRING_SENSOR;

	int SENSOR_X10[8]
	{
		455, 414,
		452, 417,
		480, 443,
		483, 439
	};
	sensorx10 = App->physics->CreateChainSensor(0, 0, SENSOR_X10, 8);
	sensorx10->body->SetType(b2_staticBody);
	sensorx10->ctype = ColliderType::SCORE_X10;

	int SENSOR_TRI_LEFT[8]
	{
		127, 531,
		109, 540,
		149, 623,
		171, 615
	};
	sensorTriLeft = App->physics->CreateChainSensor(0, 0, SENSOR_TRI_LEFT, 8);
	sensorTriLeft->body->SetType(b2_staticBody);
	sensorTriLeft->ctype = ColliderType::TRIANGLE;

	int SENSOR_TRI_RIGHT[8]
	{
		380, 533,
		397, 542,
		357, 624,
		338, 616
	};
	sensorTriRight = App->physics->CreateChainSensor(0, 0, SENSOR_TRI_RIGHT, 8);
	sensorTriRight->body->SetType(b2_staticBody);
	sensorTriRight->ctype = ColliderType::TRIANGLE;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}

void ModuleScene::DeleteMap()
{
	delete bg;
	bg = nullptr;

	delete wallLeft;
	wallLeft = nullptr;

	delete platformLeft;
	platformLeft = nullptr;
	
	delete platformRight;
	platformRight = nullptr;

	delete diamond;
	diamond = nullptr;

	delete triangle_left;
	triangle_left = nullptr;

	delete triangle_right;
	triangle_right = nullptr;

	delete frankfurt_left;
	frankfurt_left = nullptr;

	delete frankfurt_right;
	frankfurt_right = nullptr;

	delete blue;
	blue = nullptr;

	delete red;
	red = nullptr;

	delete yellow;
	yellow = nullptr;

	delete ballBody;
	ballBody = nullptr;
	
	delete springSensor;
	springSensor = nullptr;

	delete sensorx10;
	sensorx10 = nullptr;

	delete sensorTriLeft;
	sensorTriLeft = nullptr;
}