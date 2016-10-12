#ifndef __GameObject_H__
#define __GameObject_H__

#include "Globals.h"
#include "Component.h"
#include "Geometry.h"
#include "MathGeoLib\MathGeoLib.h"
#include<vector>

class GameObject
{
public:
	GameObject();
	~GameObject();

public:
	GameObject* parent;
	std::string name;
	std::vector<GameObject*> childrens;
	
	std::vector<Component*> components;

	Component* FindComponentType();
	Component* AddComponent(Component::ComponentType type);
};

#endif