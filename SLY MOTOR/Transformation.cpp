#include "Globals.h"
#include "Transformation.h"
#include "GameObject.h"

Transformation::Transformation(GameObject* _object, int _id) : Component (_object, _id)
{
	rotation = Quat::identity;
	position = float3::zero;
	scale.Set(1.f, 1.f, 1.f);
}
Transformation::~Transformation()
{}

Quat Transformation::SetRotation(float3 rot)
{
	Quat trans = rotation;
	return trans;
}
float3 Transformation::SetMove(float3 pos)
{
	float3 trans = position;
	return trans;
}
float3 Transformation::SetScale(float3 scal)
{
	float3 trans = scale;
	return trans;
}