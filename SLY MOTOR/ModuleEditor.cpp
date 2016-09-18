#include "ModuleEditor.h"
#include "Application.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	return true;
}

update_status ModuleEditor::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update(float dt)
{
	static float f = 0.0f;
	ImGui::TextColored(RED, "PORFIN FUNCIONA ESTA MIERDA");
	ImGui::InputFloat(" ", &input);
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	if (ImGui::Button("Test Window")) show_test_window ^= 1;
	if (ImGui::Button("Another Window")) show_another_window ^= 1;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	if (show_another_window)
	{
		ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(75, 500));
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::TextColored(BLUE, "MOLAA EHH");
		ImGui::End();
	}

	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}