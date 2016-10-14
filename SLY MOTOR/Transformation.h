#ifndef __Transformation_H__
#define __Transformation_H__

#include "Globals.h"
#include "Component.h"
#include "MathGeoLib\MathGeoLib.h"

class Transformation : public Component
{
public:
	Transformation(GameObject* _object, int _id);
	~Transformation();

	mat4x4* SetRotation(float3 rot);
	vec3* SetMove(float3 pos);
	vec3* SetScale(float3 scal);
};

#endif