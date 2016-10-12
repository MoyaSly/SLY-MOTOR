#include "GameObject.h"
#include "Geometry.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

Component* GameObject::FindComponentType()
{

}

Component* GameObject::AddComponent(Component::ComponentType type)
{
	Component *new_comp = nullptr;

	if (type == Component::ComponentGeometry)
		new_comp = new Geometry(this, components.size());

	return new_comp;
}