#include "ModuleEditor.h"
#include "Application.h"
#include "Primitive.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"
#include "Imgui/imgui.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	LOG("Init editor gui with imgui lib version %s", ImGui::GetVersion());
	frame_timer.Start();
	ms_timer.Start();

	return true;
}

update_status ModuleEditor::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleEditor::FillBar(Timer &timer, const int &timer_check, vector<float> &container, float new_value)
{
	if (timer.Read() > timer_check)
	{
		timer.Start();

		if (container.size() > 100)
		{
			for (int i = 1; i < container.size(); i++)
				container[i - 1] = container[i];

			container[container.size() - 1] = new_value;
		}

		else
			container.push_back(new_value);
	}
}

update_status ModuleEditor::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	FillBar(frame_timer, 1000, frames, App->GetFPS());
	FillBar(ms_timer, 1, ms, App->GetFrameMs());

	if (show_configuration)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(700, 60));
		ImGui::Begin("Configuration", &show_configuration);
		DrawApplication();
		ImGui::End();
	}

	if (show_console)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(700, 360));
		ImGui::Begin("Console", &show_console);
		DrawConsole();
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
				ImGui::MenuItem("Configuration", "4", &show_configuration);
				ImGui::MenuItem("Console", "3", &show_console);
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("Gui Demo"))
				{
					show_test_window = !show_test_window;
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

void ModuleEditor::DrawApplication()
{
	if (ImGui::CollapsingHeader("Application"))
	{
		static char app_name[120];
		strcpy_s(app_name, 120, App->GetAppName());
		if (ImGui::InputText("App Name", app_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
			App->SetAppName(app_name);

		static char org_name[120];
		strcpy_s(org_name, 120, App->GetOrganizationName());
		if (ImGui::InputText("Organization", org_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
			App->SetOrganizationName(org_name);

		int max_fps = App->GetFramerateLimit();
		if (ImGui::SliderInt("Max FPS", &max_fps, 0, 120))
			App->SetFramerateLimit(max_fps);

		ImGui::Text("Limit Framerate:");
		ImGui::SameLine();
		ImGui::TextColored(YELLOW, "%i", App->GetFramerateLimit());

		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", frames[frames.size() - 1]);
		ImGui::PlotHistogram("##framerate", &frames[0], frames.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %.1f", ms[ms.size() - 1]);
		ImGui::PlotHistogram("##framerate", &ms[0], ms.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
	/*	sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.1f", ms_log[ms_log.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

		// Memory --------------------
		sMStats stats = m_getMemoryStatistics();
		static int speed = 0;
		static vector<float> memory(100);
		if (++speed > 20)
		{
			speed = 0;
			if (memory.size() == 100)
			{
				for (uint i = 0; i < 100 - 1; ++i)
					memory[i] = memory[i + 1];

				memory[100 - 1] = (float)stats.totalReportedMemory;
			}
			else
				memory.push_back((float)stats.totalReportedMemory);
		}

		ImGui::PlotHistogram("##memory", &memory[0], memory.size(), 0, "Memory Consumption", 0.0f, (float)stats.peakReportedMemory * 1.2f, ImVec2(310, 100));

		ImGui::Text("Total Reported Mem: %u", stats.totalReportedMemory);
		ImGui::Text("Total Actual Mem: %u", stats.totalActualMemory);
		ImGui::Text("Peak Reported Mem: %u", stats.peakReportedMemory);
		ImGui::Text("Peak Actual Mem: %u", stats.peakActualMemory);
		ImGui::Text("Accumulated Reported Mem: %u", stats.accumulatedReportedMemory);
		ImGui::Text("Accumulated Actual Mem: %u", stats.accumulatedActualMemory);
		ImGui::Text("Accumulated Alloc Unit Count: %u", stats.accumulatedAllocUnitCount);
		ImGui::Text("Total Alloc Unit Count: %u", stats.totalAllocUnitCount);
		ImGui::Text("Peak Alloc Unit Count: %u", stats.peakAllocUnitCount);*/
	}
}

void ModuleEditor::DrawConsole()
{
	/*ImGui::Begin("Console", &show_console, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing);
	ImGui::TextUnformatted(buf.begin());
	if (scroll_to_bottom)
		ImGui::SetScrollHere(1.0f);
	scroll_to_bottom = false;
	ImGui::End();*/
}

void ModuleEditor::Log(const char * entry)
{
	/*if (show_console)
	{
		buf.append(entry);
		scroll_to_bottom = true;
	}
		*/
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}