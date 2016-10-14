#include "Globals.h"
#include "Transformation.h"
#include "GameObject.h"

Transformation::Transformation(GameObject* _object, int _id) : Component (_object, _id)
{}
Transformation::~Transformation()
{}

mat4x4* Transformation::SetRotation(float3 rot)
{
	mat4x4* trans = new mat4x4();
	return trans;
}
vec3* Transformation::SetMove(float3 pos)
{
	vec3* trans = new vec3();
	return trans;
}
vec3* Transformation::SetScale(float3 scal)
{
	vec3* trans = new vec3();
	return trans;
}