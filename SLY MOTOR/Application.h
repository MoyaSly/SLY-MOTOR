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

private:

	Timer	ms_timer;
	Timer	frame_time;
	float	dt;
	int		last_frame_ms = 0;
	int		last_frame_count = 0;
	int		prev_frame_count = 0;
	int		frame_count = 0;
	p2List<Module*> list_modules;

	int		ms = 1000 / 60;
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
	void SetAppName(const char* name);
	const char* GetOrganizationName() const;
	void SetOrganizationName(const char* name);
	uint GetFramerateLimit() const;
	void SetFramerateLimit(uint max_framerate);
	int GetFPS();
	int GetFrameMs();
	bool SecCounter();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};