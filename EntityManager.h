#pragma once
#include "Module.h"
#include "Entity.h"
#include "p2List.h"

class EntityManager : public Module
{
public:

	EntityManager(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	//bool Awake(pugi::xml_node&);

	// Called after Awake
	bool Start();

	// Called every frame
	update_status Update();
	
	// Called every frame
	update_status PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Entity* CreateEntity(EntityType type);

	void DestroyEntity(Entity* entity);

	void AddEntity(Entity* entity);

public:

	p2List<Entity*> entities;

};

