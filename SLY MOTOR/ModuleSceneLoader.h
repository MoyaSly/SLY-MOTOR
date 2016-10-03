#ifndef __ModuleSceneLoader_H__
#define __ModuleSceneLoader_H__

#include <string>
#include <map>
#include "Module.h"
#include "Math.h"


class ModuleSceneLoader : public Module
{
public:

	ModuleSceneLoader(Application* app, bool start_enabled = true);
	~ModuleSceneLoader();

	bool Init();
	bool Start();
	bool CleanUp();

};

#endif