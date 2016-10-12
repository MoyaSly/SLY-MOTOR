#ifndef __Component_H__
#define __Component_H__

#include "Globals.h"
#include "Application.h"
#include "MathGeoLib\MathGeoLib.h"

class GameObject;

class Component
{
public:

	enum ComponentType
	{
		ComponentGeometry
	};

	Component(GameObject* parent, int id);
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();

	ComponentType GetType();
	bool IsEnabled();

public:
	std::string name;
	GameObject* parent;
	int id;
	ComponentType type;

private:
	bool enabled;
};

#endif