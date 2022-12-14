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
#include "ModuleDebug.h"
#include "Animation.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	// Initialise all the internal class variables, at least to NULL pointer
	ray_on = false;

	App->death->OutFileRank(l);
	highScore = l[0].score;
	currentScore = 0;
	previousScore = 0;
	ballsCounter = 3;
}

ModuleScene::~ModuleScene()
{
	// You should do some memory cleaning here, if required
}

bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;
	springForce = 0;


	//Create Colliders/Sensors
	CreateColliders();
	CreateSensors();

	//Create Entities
	flipperL = (Flippers*)App->entityManager->CreateEntity(EntityType::FLIPPERS);
	ball = (Ball*)App->entityManager->CreateEntity(EntityType::BALL);

	
	// Load textures
	//img = App->textures->Load("pinball/pinball_composition.png");
	img = App->textures->Load("pinball/backgroundHole_2.png");
	top = App->textures->Load("pinball/top.png");
	assets = App->textures->Load("pinball/assets.png");
	balls = App->textures->Load("pinball/prova.png");
	lower = App->textures->Load("pinball/lower.png");
	timebar = App->textures->Load("pinball/Barra.png");
	savers = App->textures->Load("pinball/savers.png");


	//Audio
	Mix_Volume(-1, 32);
	Mix_VolumeMusic(10);
	//App->audio->PlayMusic("Assets/Audio/", 0);
	//App->audio->LoadFx("Assets/Audio/");
	sfx_intro = App->audio->LoadFx("pinball/Audio/intro.wav");
	sfx_flipper_up = App->audio->LoadFx("pinball/Audio/flipper_up.wav");
	sfx_flipper_down = App->audio->LoadFx("pinball/Audio/flipper_down.wav");
	sfx_spring = App->audio->LoadFx("pinball/Audio/spring.wav");
	sfx_bouncer_circle = App->audio->LoadFx("pinball/Audio/bouncer_circle.wav");
	sfx_bouncer_tri = App->audio->LoadFx("pinball/Audio/bouncer_tri.wav");
	sfx_trigger = App->audio->LoadFx("pinball/Audio/trigger.wav");
	sfx_comboA = App->audio->LoadFx("pinball/Audio/comboA.wav");
	sfx_comboA_done = App->audio->LoadFx("pinball/Audio/comboA_done.wav");
	sfx_new_ball = App->audio->LoadFx("pinball/Audio/new_ball.wav");
	sfx_death = App->audio->LoadFx("pinball/Audio/death.wav");
	sfx_spring = App->audio->LoadFx("pinball/Audio/spring.wav");
	sfx_game_over = App->audio->LoadFx("pinball/Audio/game_over.wav");


	//Set variables
	timeOut = false;
	previousScore = currentScore;
	currentScore = 0;
	ballsCounter = 3;
	scoreMultiplier = 0;
	time = 60*60;
	springY = 78;
	springYpos = 826;
	

	//Set Sensors
	App->scene_intro->sensorBlue_Sensed = false;
	App->scene_intro->sensorYellow_Sensed = false;
	App->scene_intro->sensorRed_Sensed = false;
	App->scene_intro->sensorTriLeft_Sensed = false;
	App->scene_intro->sensorTriRight_Sensed = false;
	App->scene_intro->sensorTime_Sensed = false;
	App->scene_intro->sensorX10_Sensed = false;
	App->scene_intro->sensorComboA1_Sensed = false;
	App->scene_intro->sensorComboA2_Sensed = false;
	App->scene_intro->sensorComboA3_Sensed = false;
	App->scene_intro->sensorComboB1_Sensed = false;
	App->scene_intro->sensorComboB2_Sensed = false;
	App->scene_intro->sensorComboB3_Sensed = false;


	//Enable/Disable Modules
	App->lights->Enable();
	App->entityManager->Enable();
	return ret;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(img);
	App->textures->Unload(assets);
	App->textures->Unload(timebar);
	App->textures->Unload(top);
	App->textures->Unload(balls);
	App->textures->Unload(lower);
	App->textures->Unload(savers);

	App->lights->Disable();
	blueLight.FullReset();
	redLight.FullReset();
	yellowLight.FullReset();
	triangleLightL.FullReset();
	triangleLightR.FullReset();
	timeLight.FullReset();
	DeleteMap();
	
	return true;
}

update_status ModuleScene::Update()
{
	//Check out of balls
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN || ballsCounter == 0 || timeOut)
	{
		App->fade->FadeBlack(this, (Module*)App->death, 90);
		App->entityManager->Disable();
	}
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {
		App->death->InFileRank(l);
	}
	//Draw spring
	SDL_Rect springRect;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		springY = springY == 30 ? 30 : springY -= 0.5;
		springYpos = springYpos == 895 ? 895 : springYpos += 1;
		springRect = { 546, 109, 14, springY };
		App->renderer->Blit(assets, 505, springYpos, &springRect);
	}
	else
	{
		springRect = { 546, 109, 14, 78 };
		App->renderer->Blit(assets, 505, 826, &springRect);
		springY = 78;
		springYpos = 826;
	}

	//Draw map
	App->renderer->Blit(img, 10, 0);

	SDL_Rect frankLRect = { 9, 156, 50, 70 };
	App->renderer->Blit(assets, 157, 330, &frankLRect);

	SDL_Rect frankRRect = { 71, 155, 50, 70 };
	App->renderer->Blit(assets, 350, 330, &frankRRect);

	App->renderer->Blit(balls, 360, 878);

	//Draw Chosen UI
	if (App->debug->changeUI)
		DrawUI_1();
	else
		DrawUI_2();

	//TIME FUNCTION
	if (time > 0)
	{
		if (time > 3600) { time = 3600; }
		time--;
	}
	else
		timeOut = true;


	RayCast();
	

	return UPDATE_CONTINUE;
}

int ModuleScene::AddScore(int score)
{
	int resultScore = score;
	resultScore *= scoreMultiplier > 0 ? scoreMultiplier : 1;
	resultScore *= App->lights->delayComboB > 0 ? 10 : 1;
	timeScore += resultScore;

	return resultScore;
}

void ModuleScene::DrawUI_1()
{
	App->fonts->BlitText(390, 878 + 2, App->fonts->black, "X ");
	App->fonts->BlitText(425, 878 + 2, App->fonts->black, ballsLeft);

	//Draws variables
	sprintf_s(high, 10, "%7d", highScore);
	sprintf_s(current, 10, "%7d", currentScore);
	sprintf_s(previous, 10, "%7d", previousScore);
	sprintf_s(ballsLeft, 3, "%d", ballsCounter);
	sprintf_s(multiplier, 5, "%2d", AddScore(1));

	App->fonts->BlitText(600, 75, App->fonts->white, "HIGHSCORE");

	App->fonts->BlitText(600, 195, App->fonts->white, "CURRENT SCORE");

	App->fonts->BlitText(600, 800, App->fonts->grey, "PREVIOUS SCORE");
	App->fonts->BlitText(800, 865, App->fonts->grey, previous);

	App->fonts->BlitText(600, 320, App->fonts->white, "MULTIPLIER");


	if ((AddScore(1)) < 2) {
		App->fonts->BlitText(900, 320, App->fonts->white, "X");
		App->fonts->BlitText(932, 320, App->fonts->white, multiplier);
	}
	else if ((AddScore(1)) >= 2 && (AddScore(1)) < 8) {
		App->fonts->BlitText(900, 320, App->fonts->yellow, "X");
		App->fonts->BlitText(932, 320, App->fonts->yellow, multiplier);
	}
	else if ((AddScore(1)) >= 8 && (AddScore(1)) < 16) {
		App->fonts->BlitText(900, 320, App->fonts->red, "X");
		App->fonts->BlitText(932, 320, App->fonts->red, multiplier);
	}
	else if ((AddScore(1)) >= 16) {
		App->fonts->BlitText(900, 320, App->fonts->blue, "X");
		App->fonts->BlitText(932, 320, App->fonts->blue, multiplier);
	}


	if (highScore > currentScore) {

		App->fonts->BlitText(800, 115, App->fonts->white, high);
		App->fonts->BlitText(800, 240, App->fonts->white, current);
	}
	else {
		highScore = currentScore;
		App->fonts->BlitText(800, 115, App->fonts->yellow, high);
		App->fonts->BlitText(800, 240, App->fonts->yellow, current);
	}
}

void ModuleScene::DrawUI_2()
{
	//choose fonts
	int multFont = App->fonts->red;
	if (AddScore(1) < 2)
		multFont = App->fonts->white;
	else if (AddScore(1) < 8)
		multFont = App->fonts->yellow;

	int scores = App->fonts->white;
	if (currentScore >= highScore)
	{
		highScore = currentScore;
		scores = App->fonts->yellow;
	}

	//Formating
	sprintf_s(high, 10, "%0d", highScore);
	sprintf_s(current, 10, "%0d", currentScore);
	sprintf_s(previous, 10, "%0d", previousScore);
	sprintf_s(ballsLeft, 3, "%0d", ballsCounter);
	sprintf_s(multiplier, 5, "%0d", AddScore(1));

	//Scores
	App->fonts->BlitText(600, 75, App->fonts->white, "HIGHSCORE");
	App->fonts->BlitText(600, 115, scores, high);

	App->fonts->BlitText(600, 195, App->fonts->white, "CURRENT SCORE");
	App->fonts->BlitText(600, 240, scores, current);

	App->fonts->BlitText(600, 800, App->fonts->grey, "PREVIOUS SCORE");
	App->fonts->BlitText(600, 865, App->fonts->grey, previous);

	App->fonts->BlitText(600, 320, App->fonts->white, "MULTIPLIER");
	std::string string = std::string("X") + std::string(multiplier);
	App->fonts->BlitText(600, 365, multFont, string.c_str());

	//Balls left
	string = std::string("X") + std::string(ballsLeft);
	App->fonts->BlitText(394, 880, App->fonts->black, string.c_str());
}

void ModuleScene::CreateColliders()
{
	//Map
	int BG[118] =
	{
		276, 930,
		276, 842,
		450, 753,
		486, 738,
		486, 483,
		469, 462,
		480, 437,
		458, 414,
		436, 429,
		422, 409,
		423, 392,
		434, 367,
		447, 332,
		453, 314,
		456, 292,
		455, 270,
		449, 245,
		434, 218,
		409, 189,
		372, 162,
		362, 150,
		364, 131,
		379, 122,
		401, 131,
		425, 147,
		446, 168,
		470, 200,
		480, 220,
		489, 243,
		494, 266,
		497, 295,
		497, 807,
		535, 807,
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
		20, 296,
		29, 363,
		42, 403,
		61, 440,
		78, 459,
		81, 470,
		74, 482,
		56, 499,
		40, 524,
		24, 553,
		24, 738,
		62, 753,
		232, 840,
		232, 930
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
	int PLATFORM_LEFT[28] =
	{
		58, 652,
		58, 663,
		64, 673,
		149, 717,
		154, 716,
		163, 698,
		162, 692,
		74, 647,
		69, 642,
		68, 635,
		68, 571,
		66, 562,
		62, 560,
		58, 569
	};
	int PLATFORM_RIGHT[28] =
	{
		451, 651,
		451, 663,
		446, 673,
		361, 717,
		355, 714,
		348, 701,
		348, 692,
		433, 649,
		439, 645,
		442, 641,
		442, 571,
		444, 563,
		448, 560,
		451, 569
	};


	bg = App->physics->CreateChain(0, 0, BG, 118);
	bg->body->SetType(b2BodyType::b2_staticBody);

	wallLeft = App->physics->CreateChain(0, 0, WALL_LEFT, 64);
	wallLeft->body->SetType(b2BodyType::b2_staticBody);

	platformLeft = App->physics->CreateChain(0, 0, PLATFORM_LEFT, 28);
	platformLeft->body->SetType(b2BodyType::b2_staticBody);

	platformRight = App->physics->CreateChain(0, 0, PLATFORM_RIGHT, 28);
	platformRight->body->SetType(b2BodyType::b2_staticBody);


	// Bounce
	//int DIAMOND[34] =
	//{
	//	205, 440,
	//	246, 420,
	//	251, 418,
	//	256, 418,
	//	261, 418,
	//	266, 419,
	//	308, 438,
	//	313, 442,
	//	314, 448,
	//	314, 454,
	//	309, 460,
	//	268, 480,
	//	257, 482,
	//	247, 480,
	//	204, 461,
	//	199, 454,
	//	199, 445
	//};
	//diamond = App->physics->CreateChain(0, 0, DIAMOND, 34);
	//diamond->body->SetType(b2BodyType::b2_staticBody);
	//diamond->ctype = ColliderType::DIAMOND;

	int TOP_LEFT_BLOCKER[12] = {
		314, 107,
		322, 115,
		322, 163,
		314, 172,
		305, 164,
		305, 116
	};

	blockerL = App->physics->CreateChain(0, 0, TOP_LEFT_BLOCKER, 12);
	blockerL->body->SetType(b2BodyType::b2_staticBody);
	blockerL->ctype = ColliderType::WALL;

	int TOP_RIGHT_BLOCKER[12] = {
	258, 108,
	266, 116,
	266, 164,
	258, 172,
	249, 165,
	249, 116
	};

	blockerR = App->physics->CreateChain(0, 0, TOP_RIGHT_BLOCKER, 12);
	blockerR->body->SetType(b2BodyType::b2_staticBody);
	blockerR->ctype = ColliderType::WALL;

	int REBOUND_LEFT[28] =
	{
		107, 529,
		100, 533,
		100, 542,
		100, 600,
		101, 608,
		105, 614,
		145, 639,
		154, 640,
		160, 637,
		165, 632,
		166, 624,
		164, 616,
		141, 572,
		115, 529
	};

	triangle_left = App->physics->CreateChain(0, 0, REBOUND_LEFT, 28);
	triangle_left->body->SetType(b2BodyType::b2_staticBody);
	
	int REBOUND_RIGHT[28] =
	{
		394, 529,
		388, 533,
		380, 554,
		344, 620,
		343, 628,
		347, 636,
		354, 640,
		365, 639,
		402, 618,
		406, 612,
		409, 601,
		409, 547,
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
	frankfurt_left->ctype = ColliderType::WALL;
	
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
	frankfurt_right->ctype = ColliderType::WALL;

	blue = App->physics->CreateCircle(190+37, 196+39, 25);
	blue->body->SetType(b2BodyType::b2_staticBody);
	blue->ctype = ColliderType::BLUE_25;

	red = App->physics->CreateCircle(300+39, 196 + 39, 25);
	red->body->SetType(b2BodyType::b2_staticBody);
	red->ctype = ColliderType::RED_100;

	yellow = App->physics->CreateCircle(246 + 37, 294 + 37, 25);
	yellow->body->SetType(b2BodyType::b2_staticBody);
	yellow->ctype = ColliderType::YELLOW_50;

	saverLeft = App->physics->CreateRectangle(42, 650, 25, 10);
	saverLeft->body->SetType(b2BodyType::b2_staticBody);
	saverLeft->ctype = ColliderType::SAVER_LEFT;

	saverRight = App->physics->CreateRectangle(468, 650, 25, 10);
	saverRight->body->SetType(b2BodyType::b2_staticBody);
	saverRight->ctype = ColliderType::SAVER_RIGHT;

}

void ModuleScene::CreateSensors()
{
	sensorSpring = App->physics->CreateRectangleSensor(515, 800, 10, 10);
	sensorSpring->ctype = ColliderType::SENSOR_SPRING;

	sensorTime = App->physics->CreateCircleSensor(112, 455, 23);
	sensorTime->ctype = ColliderType::SENSOR_TIME;

	int SENSOR_X10[8]
	{
		455, 414,
		452, 417,
		480, 443,
		483, 439
	}; 
	sensorX10 = App->physics->CreateChainSensor(0, 0, SENSOR_X10, 8);
	sensorX10->body->SetType(b2_staticBody);
	sensorX10->ctype = ColliderType::SENSOR_X10;

	int SENSOR_DEATH[6] =
	{
		223+10, 877-5,
		267+10, 877-5,
		243+10, 894-5
	};
	sensorDeath = App->physics->CreateChainSensor(0, 0, SENSOR_DEATH, 6);
	sensorDeath->body->SetType(b2_staticBody);
	sensorDeath->ctype = ColliderType::SENSOR_DEATH;

	int SENSOR_TRI_LEFT[8]
	{
		127, 531,
		109, 540,
		149, 623,
		171, 615
	};
	sensorTriLeft = App->physics->CreateChainSensor(0, 0, SENSOR_TRI_LEFT, 8);
	sensorTriLeft->body->SetType(b2_staticBody);
	sensorTriLeft->ctype = ColliderType::SENSOR_TRI_LEFT;

	int SENSOR_TRI_RIGHT[8]
	{
		380, 533,
		397, 542,
		357, 624,
		338, 616
	};
	sensorTriRight = App->physics->CreateChainSensor(0, 0, SENSOR_TRI_RIGHT, 8);
	sensorTriRight->body->SetType(b2_staticBody);
	sensorTriRight->ctype = ColliderType::SENSOR_TRI_RIGHT;

	//COMBO A
	int SENSOR_COMBO_A1[8] =
	{
		435, 229,
		429, 233,
		438, 252,
		446, 249
	};
	sensorComboA1 = App->physics->CreateChainSensor(0, 0, SENSOR_COMBO_A1, 8);
	sensorComboA1->body->SetType(b2_staticBody);
	sensorComboA1->ctype = ColliderType::SENSOR_COMBO_A1;

	int SENSOR_COMBO_A2[8] =
	{
		450, 264,
		442, 266,
		444, 288,
		452, 287
	};
	sensorComboA2 = App->physics->CreateChainSensor(0, 0, SENSOR_COMBO_A2, 8);
	sensorComboA2->body->SetType(b2_staticBody);
	sensorComboA2->ctype = ColliderType::SENSOR_COMBO_A2;

	int SENSOR_COMBO_A3[8] =
	{
		451, 305,
		443, 304,
		438, 322,
		446, 326
	};
	sensorComboA3 = App->physics->CreateChainSensor(0, 0, SENSOR_COMBO_A3, 8);
	sensorComboA3->body->SetType(b2_staticBody);
	sensorComboA3->ctype = ColliderType::SENSOR_COMBO_A3;

	//COMBO B
	int SENSOR_COMBO_B1[8] =
	{
		225, 116,
		225, 161,
		234, 161,
		234, 116,
	};
	sensorComboB1 = App->physics->CreateChainSensor(0, 0, SENSOR_COMBO_B1, 8);
	sensorComboB1->body->SetType(b2_staticBody);
	sensorComboB1->ctype = ColliderType::SENSOR_COMBO_B1;

	int SENSOR_COMBO_B2[8] =
	{
		281, 116,
		281, 161,
		290, 161,
		290, 116,
	};
	sensorComboB2 = App->physics->CreateChainSensor(0, 0, SENSOR_COMBO_B2, 8);
	sensorComboB2->body->SetType(b2_staticBody);
	sensorComboB2->ctype = ColliderType::SENSOR_COMBO_B2;

	int SENSOR_COMBO_B3[8] =
	{
		337, 116,
		337, 161,
		346, 161,
		346, 116
	};
	sensorComboB3 = App->physics->CreateChainSensor(0, 0, SENSOR_COMBO_B3, 8);
	sensorComboB3->body->SetType(b2_staticBody);
	sensorComboB3->ctype = ColliderType::SENSOR_COMBO_B3;
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
	
	delete sensorSpring;
	sensorSpring = nullptr;

	delete sensorX10;
	sensorX10 = nullptr;

	delete sensorDeath;
	sensorDeath = nullptr;

	delete sensorTriLeft;
	sensorTriLeft = nullptr;
	delete sensorTriRight;
	sensorTriRight = nullptr;

	delete sensorComboA1;
	sensorComboA1 = nullptr;
	delete sensorComboA2;
	sensorComboA2 = nullptr;
	delete sensorComboA3;
	sensorComboA3 = nullptr;

	delete sensorComboB1;
	sensorComboB1 = nullptr;
	delete sensorComboB2;
	sensorComboB2 = nullptr;
	delete sensorComboB3;
	sensorComboB3 = nullptr;

	delete sensorTime;
	sensorTime = nullptr;

	delete blockerL;
	blockerL = nullptr;

	delete blockerR;
	blockerR = nullptr;

	delete saverLeft;
	saverLeft = nullptr;
	delete saverRight;
	saverRight = nullptr;
}

void ModuleScene::RayCast()
{
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
	if (ray_on == true)
	{
		// Compute the vector from the raycast origin up to the contact point (if we're hitting anything; otherwise this is the reference length)
		fVector destination(mouse.x - ray.x, mouse.y - ray.y);
		destination.Normalize();
		destination *= ray_hit;

		// Draw a line from origin to the hit point (or reference length if we are not hitting anything)
		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		// If we are hitting something with the raycast, draw the normal vector to the contact point
		if (normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}
}