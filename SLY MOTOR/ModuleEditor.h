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
	void Log(const char* entry);
	bool CleanUp();

private:
	void FillBar(Timer &timer, const int &timer_check, std::vector<float> &container, float new_value);

	bool show_test_window = false;
	bool show_configuration = true;
	bool show_menu_bar = true;
	bool show_console = true;
	bool scroll_to_bottom = true;

private:
	Timer frame_timer;
	Timer ms_timer;
	std::vector<float> ms_log;
	std::vector<float> frames_log;
	//ImGuiTextBuffer buf;
	
};
#endif
