#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

	SDL_Window* GetWindow() const;

	// WIDHT & HEIGHT SCREEN
	uint GetWidth() const;
	uint GetHeight() const;
	void SetWidth(uint width);
	void SetHeigth(uint height);
	void GetMaxMinSize(uint& min_w, uint& min_h, uint& max_w, uint& max_h) const;
	void OnResize(int width, int height);

	// TYPE SCREEN
	bool IsFullscreen() const;
	bool IsResizable() const;
	bool IsBorderless() const;
	bool IsFullscreenDesktop() const;

	void SetFullscreen(bool set);
	void SetResizable(bool set);
	void SetBorderless(bool set);
	void SetFullScreenDesktop(bool set);

	// BRIGHTNESS
	float GetBrightness() const;
	void SetBrightness(float set);

private:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

	uint screen_width;
	uint screen_height;
	bool fullscreen = false;
	bool resizable = false;
	bool borderless = false;
	bool fullscreen_desktop = false;

};
#endif