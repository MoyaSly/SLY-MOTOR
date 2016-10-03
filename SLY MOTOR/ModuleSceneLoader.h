#ifndef __ModuleSceneLoader_H__
#define __ModuleSceneLoader_H__

#include "Module.h"
#include "MathGeoLib\MathGeoLib.h"


struct Geometry;

class ModuleSceneLoader : public Module
{
public:

	ModuleSceneLoader(Application* app, bool start_enabled = true);
	~ModuleSceneLoader();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	std::vector<const Geometry*> geo;

private:

	void LoadFile(const char *file);

};

#endif