#include "Globals.h"
#include "Transformation.h"
#include "GameObject.h"
#include "MathGeoLib/MathBuildConfig.h"
#include "MathGeoLib/MathGeoLib.h"


Transformation::Transformation(GameObject* _object, int _id) : Component (_object, _id)
{
	/*rotation = Quat::identity;
	position = float3::zero;
	scale.Set(1.f, 1.f, 1.f);*/
}
Transformation::~Transformation()
{}

//POSITION
void Transformation::SetPosition(float3 pos) { position = pos; }
float3 Transformation::GetPosition() { return position; }
void Transformation::ResetPosition() { position = float3::zero; }

//ROTATION
void Transformation::SetRotation(float3 rot)
{
	if (rot.x < 0)
		rot.x += 360;
	if (rot.y < 0)
		rot.y += 360;
	if (rot.z < 0)
		rot.z += 360;

	rot *= DEGTORAD;
	
	rotation = Quat::FromEulerXYZ(rot.x, rot.y, rot.z);
}

float3 Transformation::GetRotation()
{
	float3 rot = rotation.ToEulerXYZ();

	rot * RADTODEG;

	if (rot.x < 0)
		rot.x += 360;
	if (rot.y < 0)
		rot.y += 360;
	if (rot.z < 0)
		rot.z += 360;

	return rot;
}

void Transformation::ResetRotation() { SetRotation(float3::zero); }


//SCALE
void Transformation::SetScale(float3 scal) 
{ 
	if (scal.x != 0 && scal.y != 0 && scal.z != 0) 
		scale = scal;
}
float3 Transformation::GetScale() { return scale; }
void Transformation::ResetScale() { scale.Set(1.f, 1.f, 1.f); }