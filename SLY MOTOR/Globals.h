#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI


typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 800
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "MOTOR SLY"

#define GREY ImVec4(0.6f,0.6f,0.6f,1.f)
#define BLUE ImVec4(0.2f,0.2f,1.f,1.f)
#define GREEN ImVec4(0.f,1.f,0.f,1.f)
#define YELLOW ImVec4(1.f,1.f,0.f,1.f)
#define RED ImVec4(1.f,0.f,0.f,1.f)
#define WHITE ImVec4(1.f,1.f,1.f,1.f)