#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "PerfTimer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModuleEditor.h"
#include "ModuleSceneLoader.h"

using namespace std;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModulePhysics3D* physics;
	ModuleEditor* editor;
	ModuleSceneLoader* scene_loader;

private:

	Timer ms_timer;
	Timer fps_timer;
	Uint32 frames;
	float dt;
	int	fps_counter;
	int	last_frame_ms;
	int	last_fps;
	p2List<Module*> list_modules;

	int	ms;
	string app_name;
	string org_name;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void RequestBrowser(const char* url) const;
	const char* GetAppName() const;
	const char* GetOrgName() const;
	uint GetFramerateLimit() const;
	void SetFramerateLimit(uint max_framerate);
	int GetFrameMs();


private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};