#include "EntityManager.h"
#include "Flippers.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleSceneIntro.h"

#include "Defs.h"
#include "Globals.h"

EntityManager::EntityManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
//bool EntityManager::Awake(pugi::xml_node& config)
//{
//	LOG("Loading Entity Manager");
//	bool ret = true;
//
//	//Iterates over the entities and calls the Awake
//	ListItem<Entity*>* item;
//	Entity* pEntity = NULL;
//
//	for (item = entities.start; item != NULL && ret == true; item = item->next)
//	{
//		pEntity = item->data;
//
//		if (pEntity->active == false) continue;
//		ret = item->data->Awake();
//	}
//
//	return ret;
//
//}

bool EntityManager::Start() {

	LOG("Entity_Manager");

	bool ret = true; 

	//Iterates over the entities and calls Start
	p2List_item<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Start();
	}

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	p2List_item<Entity*>* item;
	item = entities.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	entities.clear();

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type)
{
	Entity* entity = nullptr; 

	//L02: DONE 2: Instantiate entity according to the type and add the new entoty it to the list of Entities

	switch (type)
	{

	/*case EntityType::PLAYER:
		entity = new ModulePlayer();
		break;*/

	default: break;
	}

	// Created entities are added to the list
	AddEntity(entity);

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	p2List_item<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity) entities.del(item);
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	if ( entity != nullptr) entities.add(entity);
}

update_status EntityManager::Update()
{
	bool ret = true;
	p2List_item<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Update();
	}

	return ret ? UPDATE_CONTINUE : UPDATE_ERROR;
}