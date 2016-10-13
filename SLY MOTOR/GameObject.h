#ifndef __GameObject_H__
#define __GameObject_H__

#include "Globals.h"
#include "MathGeoLib\MathGeoLib.h"
#include<vector>

class Component;
enum ComponentType;

class GameObject
{
public:
	GameObject();
	~GameObject();

public:
	GameObject* parent;
	std::string name;
	std::vector<GameObject*> childrens;
	
	std::vector<Component*> cmp;

	//Component* FindComponentType();
	Component* AddComponent(ComponentType type);
};

#endif