#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__

#include "Module.h"
#include "Globals.h"
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
	void DrawApplication();
	bool CleanUp();

	bool show_test_window = false;
	bool show_configuration = true;
	bool show_menu_bar = true;
	bool show_console = true;

private:
	std::vector<float> fps_log;
	std::vector<float> ms_log;
};
#endif
