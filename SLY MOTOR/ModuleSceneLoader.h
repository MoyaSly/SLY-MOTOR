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
	void LoadFile(const char* file);

private:

	uint id_vertices = 0; // id in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_indices = 0; // id in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

};

#endif