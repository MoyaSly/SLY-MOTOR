#ifndef __Transformation_H__
#define __Transformation_H__

#include "Component.h"

class Transformation : public Component
{
public:
	Transformation(GameObject* _object, int _id);
	~Transformation();

	//POSITION
	void SetPosition(float3 pos);
	float3 GetPosition();
	void ResetPosition();

	//ROTATION
	void SetRotation(float3 rot);
	float3 GetRotation();
	void ResetRotation();

	//SCALE
	void SetScale(float3 scal);
	float3 GetScale();
	void ResetScale();


private:
	float3 position;
	Quat rotation;
	float3 scale;

};

#endif