#include "GameObject.h"
#include "Geometry.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

/*Component* GameObject::FindComponentType()
{

}*/

Component* GameObject::AddComponent(ComponentType type)
{
	Component *new_comp = nullptr;

	//if (type == ComponentGeometry)
		new_comp = new Geometry(this, cmp.size());

	return new_comp;
}