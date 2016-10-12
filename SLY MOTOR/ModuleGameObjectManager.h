#ifndef __ModulegameObjectManager_H__
#define __ModulegameObjectManager_H__

#include "Module.h"
#include "MathGeoLib\MathGeoLib.h"
#include "GameObject.h"
#include "Glew\include\glew.h"


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

	GameObject* CreateNewGameObject(GameObject* parent, const aiNode* node, const aiScene* scene);
	std::vector<Geometry*> geo;
	bool geometry_loaded = false;
	uint texture;
	GameObject *root = NULL;

	void LoadGeometry(const char *file);
	uint LoadIMG(char *path);
	
};

#endif
