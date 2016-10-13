#ifndef __Component_H__
#define __Component_H__

#include "Globals.h"
#include "Application.h"
#include "MathGeoLib\MathGeoLib.h"

class GameObject;

enum ComponentType
{
	ComponentGeometry
};

class Component
{
public:

	Component(GameObject* _object, int _id) {}
	virtual ~Component() {}

	virtual void Enable()
	{
		if (enabled == false) 
		{ 
			enabled = true; 
		}
	}

	virtual update_status Update() { return UPDATE_CONTINUE; }

	virtual void Disable()
	{
		if (enabled == true) 
		{ 
			enabled = false; 
		}
	}

	ComponentType GetType() { return type; }
	bool IsEnabled() { return enabled; };

public:
	std::string name;
	GameObject* object;
	int id;
	ComponentType type;

private:
	bool enabled;
};

#endif