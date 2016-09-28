#include "ModuleEditor.h"
#include "Application.h"
#include "Primitive.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"
#include "Imgui/imgui.h"
#include "gpudetect/DeviceId.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled), frames_log(100), ms_log(100)
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

	App->window->GetMaxMinSize(min_w, min_h, max_w, max_h);
	w = App->window->GetWidth();
	h = App->window->GetHeight();

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
	FillBar(frame_timer, 1000, frames_log, App->GetFramerateLimit());
	FillBar(ms_timer, 1, ms_log, App->GetFrameMs());

	if (show_configuration)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(700, 60));
		ImGui::Begin("Configuration", &show_configuration);
		DrawConfiguration();
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

void ModuleEditor::DrawConfiguration()
{
	if (ImGui::CollapsingHeader("Application"))
	{
		// APP NAME
		static char app_name[120];
		strcpy_s(app_name, 120, App->GetAppName());
		if (ImGui::InputText("App Name", app_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll));

		// ORG NAME
		static char org_name[120];
		strcpy_s(org_name, 120, App->GetOrgName());
		if (ImGui::InputText("Organization", org_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll));

		// MAX FPS
		int max_fps = App->GetFramerateLimit();
		if (ImGui::SliderInt("Max FPS", &max_fps, 0, 125))
			App->SetFramerateLimit(max_fps);

		ImGui::TextColored(YELLOW, "Limit Framerate:");
		ImGui::SameLine();
		ImGui::TextColored(BLUE, "%i", App->GetFramerateLimit());
		
		char title[25];

		// GRAPH FRAMERATE
		sprintf_s(title, 25, "Framerate %.1f", frames_log[frames_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &frames_log[0], frames_log.size(), 0, title, 0.0f, 150.0f, ImVec2(310, 100));

		// GRAPH MILLISECONDS
		sprintf_s(title, 25, "Milliseconds %.1f", ms_log[ms_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &ms_log[0], ms_log.size(), 0, title, 0.0f, 50.0f, ImVec2(310, 100));
	}

	if (ImGui::CollapsingHeader("Window"))
	{
		//BRIGHTNESS
		float brightness = App->window->GetBrightness();
		if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f))
			App->window->SetBrightness(brightness);

		//WIDTH HEIGHT
		if (ImGui::SliderInt("Width", (int*)&w, min_w, max_w))
			App->window->SetWidth(w);

		if (ImGui::SliderInt("Height", (int*)&h, min_h, max_h))
			App->window->SetHeigth(h);

		bool fullscreen = App->window->IsFullscreen();
		bool resizable = App->window->IsResizable();
		bool borderless = App->window->IsBorderless();
		bool full_desktop = App->window->IsFullscreenDesktop();
		
		//FULLSCREEN
		if (ImGui::Checkbox("Fullscreen", &fullscreen))
			App->window->SetFullscreen(fullscreen);

		ImGui::SameLine();

		//RESIZABLE
		if (ImGui::Checkbox("Resizable", &resizable))
			App->window->SetResizable(resizable);

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Restart to apply");

		//BORDERLESS
		if (ImGui::Checkbox("Borderless", &borderless))
			App->window->SetBorderless(borderless);

		ImGui::SameLine();

		//FULL DESKTOP
		if (ImGui::Checkbox("Full Desktop", &full_desktop))
			App->window->SetFullScreenDesktop(full_desktop);
	}

	//HARDWARE OP
	if (ImGui::CollapsingHeader("Hardware"))
	{
		ImGui::TextColored(YELLOW, "Num CPUs: ");
		ImGui::SameLine(); ImGui::TextColored(BLUE, "%d (Cache: %dkb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());

		ImGui::TextColored(YELLOW, "Mem RAM: ");
		ImGui::SameLine(); ImGui::TextColored(BLUE, "%.2fGb", (float)SDL_GetSystemRAM() / 1024);

		ImGui::TextColored(YELLOW, "Caps: ");
		ImGui::SameLine();
		string tmp;

		if (SDL_Has3DNow) tmp += "3DNow, ";
		if (SDL_HasAVX) tmp += "AVX, ";
		if (SDL_HasAltiVec) tmp += "AltiVec, ";
		if (SDL_HasMMX) tmp += "MMX, ";
		if (SDL_HasRDTSC) tmp += "RDTSC, ";
		if (SDL_HasSSE) tmp += "SSE, ";
		if (SDL_HasSSE2) tmp += "SSE2, ";
		if (SDL_HasSSE3) tmp += "SSE3, ";
		if (SDL_HasSSE41) tmp += "SSE41, ";
		if (SDL_HasSSE42) tmp += "SSE42, ";

		ImGui::TextColored(BLUE, tmp.c_str());

		uint vendor, device_id;
		std::wstring brand;
		unsigned __int64 video_mem_budget;
		unsigned __int64 video_mem_usage;
		unsigned __int64 video_mem_available;
		unsigned __int64 video_mem_reserved;

		if (getGraphicsDeviceInfo(&vendor, &device_id, &brand, &video_mem_budget, &video_mem_usage, &video_mem_available, &video_mem_reserved))
		{
			uint gpu_vendor = vendor;
			uint gpu_device = device_id;
			std::string gpu_brand(brand.begin(), brand.end());
			float vram_mb_budget = float(video_mem_budget) / 1073741824.0f;
			float vram_mb_usage = float(video_mem_usage) / (1024.f * 1024.f * 1024.f);
			float vram_mb_available = float(video_mem_available) / (1024.f * 1024.f * 1024.f);
			float vram_mb_reserved = float(video_mem_reserved) / (1024.f * 1024.f * 1024.f);

			ImGui::TextColored(YELLOW, "GPU Brand");
			ImGui::SameLine(); ImGui::TextColored(BLUE, gpu_brand.c_str());
			ImGui::TextColored(YELLOW, "GPU Vendor");
			ImGui::SameLine(); ImGui::TextColored(BLUE, "%d", gpu_device);
			ImGui::TextColored(YELLOW, "GPU Device Id");
			ImGui::SameLine(); ImGui::TextColored(BLUE, "%d", device_id);
			ImGui::TextColored(YELLOW, "VRAM Budget");
			ImGui::SameLine(); ImGui::TextColored(BLUE, "%.2fMb", vram_mb_budget* 1024.f);
			ImGui::TextColored(YELLOW, "VRAM Usage");
			ImGui::SameLine(); ImGui::TextColored(BLUE, "%.2fMb", vram_mb_usage* 1024.f);
			ImGui::TextColored(YELLOW, "VRAM Aviable");
			ImGui::SameLine(); ImGui::TextColored(BLUE, "%.2fMb", vram_mb_available* 1024.f);
			ImGui::TextColored(YELLOW, "VRAM Reserved");
			ImGui::SameLine(); ImGui::TextColored(BLUE, "%.2fMb", vram_mb_reserved* 1024.f);
		}
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