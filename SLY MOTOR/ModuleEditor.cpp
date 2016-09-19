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
	update_status ret = UPDATE_CONTINUE;
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

	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}

	if (show_menu_bar)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Quit", "ESC"))
					ret = UPDATE_STOP;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("Gui Demo"))
				{
					show_test_window = true;
				}

				if (ImGui::MenuItem("Documentation"))
					App->RequestBrowser("https://github.com/MoyaSly/SLY-MOTOR/wiki");

				if (ImGui::MenuItem("Download latest"))
					App->RequestBrowser("https://github.com/MoyaSly/SLY-MOTOR/releases");

				if (ImGui::MenuItem("Report a bug"))
					App->RequestBrowser("https://github.com/MoyaSly/SLY-MOTOR/issues");
				ImGui::EndMenu();
			}
				ImGui::EndMainMenuBar();
		}
	}
	return ret;
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