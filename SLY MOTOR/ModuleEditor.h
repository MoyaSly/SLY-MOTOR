#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__

#include "Module.h"
#include "Globals.h"

class ModuleEditor : public Module
{

public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


	bool show_test_window = true;
	bool show_another_window = false;
	bool show_menu_bar = true;
	float input = 0;
};
#endif
