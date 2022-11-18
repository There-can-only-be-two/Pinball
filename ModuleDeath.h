#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include <list>
#include "SString.h"
#include <string>
struct Scores {
	string name;
	int score;
};

class PhysBody;

class ModuleDeath : public Module
{
public:

	// Constructors & Destructors
	ModuleDeath(Application* app, bool start_enabled);
	~ModuleDeath();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();
	void AddScore(Scores l[], int current);
	
	// Swap to write scores in order so it can be a ranking
	void SwapRank(Scores l[]);
	// Write names and scores in the .txt file
	void InFileRank(Scores l[]);
	// Extract names out of the.txt
	void OutFileRank(Scores l[]);
	void ResetRank(Scores l[]);

public:

	// Lists of physics objects
	Scores ranking[5];// = { {"XAVI", 1000000}, {"HECTOR", 99000}, {"JULS", 69000}, {"JAN", 42000}, {"YOU", score } };
	int score;

	// Textures
	SDL_Texture* img;
	
	// FX
	uint currentScore;
	// to store each highscore
	uint* ranks;
};
