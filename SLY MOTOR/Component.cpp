#include "Component.h"
#include "ImGui\imgui.h"


Component::Component(GameObject* _parent, int _id)
{
	parent = _parent;
	id = _id;
	name = "Component Empty";
	enabled = false;
}

Component::~Component()
{
}

void Component::Enable()
{
	if (enabled == false)
	{
		enabled = true;
	}
}

void Component::Disable()
{
	if (enabled == true)
	{
		enabled = false;
	}
}

void Component::Update()
{
	if (enabled)
	{
	}
}

ComponentType Component::GetType()
{
	return type;
}

bool Component::IsEnabled()
{
	return enabled;
}

