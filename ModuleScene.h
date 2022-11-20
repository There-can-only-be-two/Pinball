#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Entity.h"
#include "Animation.h"
#include "ModuleDeath.h"

class PhysBody;

class ModuleScene : public Module
{
public:

	// Constructors & Destructors
	ModuleScene(Application* app, bool start_enabled);
	~ModuleScene();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();

	int AddScore(int score);
	void DrawUI_1();
	void DrawUI_2();
	void CreateColliders();
	void CreateSensors();
	void DeleteMap();
	void RayCast();

public:
	//Variables
	int springForce;
	int springY, springYpos;

	// Lists of physics objects
	p2List<PhysBody*> entityList;
	
	//Map
	PhysBody* bg;
	PhysBody* wallLeft;
	PhysBody* platformLeft;
	PhysBody* platformRight;
	PhysBody* ballBody;
	PhysBody* saverLeft;
	PhysBody* saverRight;
	
	// Bounce
	PhysBody* diamond;
	PhysBody* triangle_left;
	PhysBody* triangle_right;
	PhysBody* frankfurt_left;
	PhysBody* frankfurt_right;
	PhysBody* blue;
	PhysBody* yellow;
	PhysBody* red;
	PhysBody* blockerL;
	PhysBody* blockerR;
	//PhysBody* flipperLeft;
	//PhysBody* flipperRight;

	//Entities
	Entity* flipperL;
	//Entity* flipperR;
	Entity* ball;

	//Sensors
	bool sensorBlue_Sensed;
	bool sensorYellow_Sensed;
	bool sensorRed_Sensed;
	bool saverLeftSensed;
	bool saverRightSensed;

	PhysBody* sensorSpring;
	bool sensorSpring_Sensed;
	PhysBody* sensorX10;
	bool sensorX10_Sensed;
	PhysBody* sensorDeath;
	bool sensorDeath_Sensed;
	PhysBody* sensorTriLeft;
	bool sensorTriLeft_Sensed;
	PhysBody* sensorTriRight;
	bool sensorTriRight_Sensed;
	PhysBody* sensorTime;
	bool sensorTime_Sensed;

	PhysBody* sensorComboA1;
	bool sensorComboA1_Sensed;
	PhysBody* sensorComboA2;
	bool sensorComboA2_Sensed;
	PhysBody* sensorComboA3;
	bool sensorComboA3_Sensed;

	PhysBody* sensorComboB1;
	bool sensorComboB1_Sensed;
	PhysBody* sensorComboB2;
	bool sensorComboB2_Sensed;
	PhysBody* sensorComboB3;
	bool sensorComboB3_Sensed;

	// Textures
	SDL_Texture* img;
	SDL_Texture* top;
	SDL_Texture* balls;
	SDL_Texture* assets;
	SDL_Texture* lower;
	SDL_Texture* timebar;
	SDL_Texture* savers;

	//Animations
	Animation blueLight;
	Animation redLight;
	Animation yellowLight;
	Animation triangleLightL;
	Animation triangleLightR;
	Animation timeLight;

	//scores
	char high[10] = { "\0" };
	uint highScore = 0;
	char current[10] = { "\0" };
	uint currentScore = 0;
	char previous[10] = { "\0" };
	uint previousScore = 0;
	char ballsLeft[3] = { "\0" };
	uint ballsCounter = 0;
	char multiplier[5] = { "\0" };
	int scoreMultiplier;
	int timeScore;
	int time;
	bool timeOut;
	Scores l[5];

	//SFX
	uint sfx_intro;
	uint sfx_flipper_up;
	uint sfx_flipper_down;
	uint sfx_spring;
	uint sfx_bouncer_circle;
	uint sfx_bouncer_tri;
	uint sfx_trigger;
	uint sfx_comboA;
	uint sfx_new_ball;
	uint sfx_death;
	uint sfx_game_over;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};
