#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl3.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	screen_width = SCREEN_WIDTH;
	screen_height = SCREEN_HEIGHT;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{

		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(WIN_FULLSCREEN == true)
			flags |= SDL_WINDOW_FULLSCREEN;

		if(WIN_RESIZABLE == true)
			flags |= SDL_WINDOW_RESIZABLE;
		

		if(WIN_BORDERLESS == true)
			flags |= SDL_WINDOW_BORDERLESS;

		if(WIN_FULLSCREEN_DESKTOP == true)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		SDL_DisplayMode current;
		SDL_GetCurrentDisplayMode(0, &current);
		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);

			//ImGui
			ImGui_ImplSdlGL3_Init(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

uint ModuleWindow::GetWidth() const
{
	return screen_width;
}

uint ModuleWindow::GetHeight() const
{
	return screen_height;
}

void ModuleWindow::SetWidth(uint width)
{
	screen_width = width;
	OnResize(screen_width, screen_height);
}

void ModuleWindow::SetHeigth(uint height)
{
	screen_height = height;
	OnResize(screen_width, screen_height);
}

void ModuleWindow::GetMaxMinSize(uint& min_w, uint& min_h, uint& max_w, uint& max_h) const
{
	min_w = 640;
	min_h = 480;
	max_w = 1920;
	max_h = 1080;

	SDL_DisplayMode dm;

	if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
	{
		LOG("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
	}
	else
	{
		max_w = dm.w;
		max_h = dm.h;
	}

}


void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

float ModuleWindow::GetBrightness() const
{
	return SDL_GetWindowBrightness(window);
}

void ModuleWindow::SetBrightness(float set)
{
	CAP(set);
	if (SDL_SetWindowBrightness(window, set) != 0)
		LOG("Could not change window brightness: %s\n", SDL_GetError());
}

SDL_Window * ModuleWindow::GetWindow() const
{
	return window;
}

void ModuleWindow::OnResize(int width, int height)
{
	SDL_SetWindowSize(window, width, height);
}
