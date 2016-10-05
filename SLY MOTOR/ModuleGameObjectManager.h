#ifndef __ModulegameObjectManager_H__
#define __ModulegameObjectManager_H__

#include "Module.h"
#include "MathGeoLib\MathGeoLib.h"
#include "GameObject.h"


class ModuleGameObjectManager : public Module
{
public:

	ModuleGameObjectManager(Application* app, bool start_enabled = true);
	~ModuleGameObjectManager();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	//GameObject* CreateNewGameObject(std::string name, GameObject* parent = NULL);


	std::vector<const Geometry*> geo;
	void LoadGeometry(const char *file);



};

#endif
