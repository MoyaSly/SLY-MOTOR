#ifndef __ModulegameObjectManager_H__
#define __ModulegameObjectManager_H__

#include "Module.h"
#include "MathGeoLib\MathGeoLib.h"
#include "Glew\include\glew.h"
#include "GameObject.h"
#include <vector>

struct aiMesh;
struct aiNode;
struct aiScene;
class GameObject;

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

	GameObject* CreateNewGameObject(const aiNode* node,  const aiScene* scene, GameObject* parent = NULL);
	std::vector<Geometry*> geo;
	bool geometry_loaded = false;
	uint texture = 0;
	GameObject* root = nullptr;

	void LoadGeometry(const char *file);
	uint LoadIMG(char *path);
	
};

#endif
