#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "SString.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "Application.h"

class PhysBody;

enum class EntityType
{
	FLIPPERS,
	ITEM,
	UNKNOWN
};

class Entity
{
public:

	Entity(EntityType type, Application* App = nullptr) : type(type), active(true) {}

	virtual bool Awake()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Update()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	/*virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&)
	{
		return true;
	}*/

	void Entity::Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}

	void Entity::Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}

	virtual void OnCollision(PhysBody* physA, PhysBody* physB) {
	
	};

public:

	SString name;
	EntityType type;
	bool active = true;
	Application* App = nullptr;
	//pugi::xml_node parameters;

	// Possible properties, it depends on how generic we
	// want our Entity class, maybe it's not renderable...
	iPoint position;       
	bool renderable = true;
};

#endif // __ENTITY_H__