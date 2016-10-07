#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glut/glut.h"

#pragma comment (lib, "glut/glut32.lib")



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG_ME("Loading Intro assets");
	return true;

}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG_ME("Unloading Intro scene");
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	glColor3f(1.f, 1.f, 1.f);
	MyPlane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	/*float x = 0.5f;
	float y = 0.5f;
	float z = 0.5f;

	glBegin(GL_TRIANGLES);
	glColor3f(10.f, 0.f, 0.f);

	//CARA +Z
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, y, z);

	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, -y, z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);

	//CARA -Z
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(x, y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);

	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, -y, -z);

	//CARA -Y
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);

	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(x, -y, -z);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);

	//CARA +Y
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);

	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);

	//CARA +X
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);

	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(x, -y, -z);

	//CARA -X
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, z);

	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);

	glEnd();*/
	return UPDATE_CONTINUE;
}
