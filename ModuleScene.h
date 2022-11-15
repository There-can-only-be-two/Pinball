#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Entity.h"
#include "Animation.h"

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

	void CreateColliders();
	void CreateSensors();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void DeleteMap();
public:

	// Lists of physics objects
	p2List<PhysBody*> entityList;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> circles;
	p2List<PhysBody*> ricks;
	
	//Map
	PhysBody* bg;
	PhysBody* wallLeft;
	PhysBody* platformLeft;
	PhysBody* platformRight;
	PhysBody* ballBody;
	
	// Bounce
	PhysBody* diamond;
	PhysBody* triangle_left;
	PhysBody* triangle_right;
	PhysBody* frankfurt_left;
	PhysBody* frankfurt_right;
	PhysBody* blue;
	PhysBody* yellow;
	PhysBody* red;
	/*PhysBody* flipperLeft;
	PhysBody* flipperRight;*/

	//Entities
	Entity* flipperL;
	//Entity* flipperR;
	Entity* ball;

	//Sensors
	PhysBody* springSensor;
	bool spring_Sensed;
	bool sensed;
	PhysBody* scorex10sensor;
	bool scorex10_Sensed;
	PhysBody* ballsensor;
	bool ball_Sensed;
	PhysBody* sensorTriLeft;
	bool sensorTriLeft_Sensed;
	PhysBody* sensorTriRight;
	bool sensorTriRight_Sensed;
	PhysBody* timeSensor;
	bool timeSensor_Sensed;

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
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* img;
	SDL_Texture* top;
	SDL_Texture* balls;
	SDL_Texture* assets;

	Animation blueLight;
	Animation redLight;
	Animation yellowLight;
	Animation triangleLightL;
	Animation triangleLightR;
	Animation timeLight;

	//scores
	int font, fontHype, fontBalls, fontPixelWhite;
	char high[10] = { "\0" };
	uint highScore = 0;
	char current[10] = { "\0" };
	uint currentScore = 0;
	char previous[10] = { "\0" };
	uint previousScore = 0;
	char ballsLeft[3] = { "\0" };
	uint ballsCounter = 0;

	// FX
	uint intro;
	uint flipper;
	uint spring;
	uint bouncer_circle;
	uint bouncer_tri_1;
	uint bouncer_tri_2;
	uint trigger;
	uint comboA;
	uint new_ball;
	uint death;
	uint game_over;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};
