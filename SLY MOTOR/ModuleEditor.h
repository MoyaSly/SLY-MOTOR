#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__

#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "Timer.h"
#include <vector>

class ModuleEditor : public Module
{

public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	void DrawConfiguration();
	void DrawConsole();
	void DrawOutliner();
	void DrawGOLoader();
	void DrawAtributeEditor();
	update_status DrawMenuBar(update_status ret);
	void Log(const char* entry);
	bool CleanUp();

private:
	void FillBar(Timer &timer, const int &timer_check, std::vector<float> &container, float new_value);

	bool show_test_window;
	bool show_configuration;
	bool show_menu_bar;
	bool show_console;
	bool scroll_to_bottom;
	bool show_outliner;
	bool show_gameobject_loader;
	bool show_atribute_editor;

private:
	Timer frame_timer;
	Timer ms_timer;
	std::vector<float> ms_log;
	std::vector<float> frames_log;
	uint w, h, min_w, min_h, max_w, max_h;
	char fbx_name[256];
	int translation[3] = { 0, 0, 0 };
	int rotation[3] = { 0, 0, 0 };
	int scale[3] = { 0, 0, 0 };
	//ImGuiTextBuffer buf;
	
};
#endif
