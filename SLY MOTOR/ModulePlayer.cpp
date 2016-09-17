#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModulePlayer::Reset()
{
	LOG("Player Reset Successfully!");
	ResetVehicle(0, 0, 0, 0);
	return true;
}

float ModulePlayer::GetSpeed()
{
	return vehicle->GetKmh();
}

btVector3 ModulePlayer::GetForwardVec3()
{
		return vehicle->vehicle->getForwardVector();;
}

vec3 ModulePlayer::GetPosition()
{
	vec3 position;
	btTransform a = vehicle->body->getWorldTransform();
	position.Set(a.getOrigin().getX(), a.getOrigin().getY(), a.getOrigin().getZ());
	return position;
}

void ModulePlayer::ResetVehicle(float x, float y, float z, float angle)
{
	vehicle->SetPos(x, y, z);
	vehicle->StopMotion();
	vehicle->Orient(angle);
	elevators->SetPos(x + 0.0f, y + 3.0f, z + 10.0f);
}