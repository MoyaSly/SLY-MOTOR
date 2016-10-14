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

	Quat rotation;
	float3 position;
	float3 scale;

	Quat SetRotation(float3 rot);

	float3 SetMove(float3 pos);
	float3 SetScale(float3 scal);



};

#endif