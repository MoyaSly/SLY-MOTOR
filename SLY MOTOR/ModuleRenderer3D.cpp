#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "Geometry.h"
#include "Glew\include\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl3.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib")  /* link Glew lib   */

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{
}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG_ME("Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->GetWindow());
	if(context == NULL)
	{
		LOG_ME("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	GLenum gl_enum = glewInit();

	if (gl_enum != GLEW_OK)
		LOG_ME("Glew hasn't been initialized!");
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG_ME("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG_ME("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG_ME("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG_ME("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	Color c = App->camera->background;
	glClearColor(c.r, c.g, c.b, c.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	ImGui_ImplSdlGL3_NewFrame(App->window->GetWindow());

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	for (int i = 0; i < App->game_object_manager->geo.size(); ++i)
	{
		DrawGeometry(App->game_object_manager->geo[i]);
	}
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	// Rendering
	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	ImGui::Render();

	SDL_GL_SwapWindow(App->window->GetWindow());
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG_ME("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool ModuleRenderer3D::LoadGeometryBuffer(const Geometry *geometry)
{
	bool ret = true;

	// VERTICES
	glGenBuffers(1, (GLuint*) &(geometry->id_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, geometry->id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * geometry->num_vertices * 3, geometry->vertices, GL_STATIC_DRAW);

	// NORMALS
	glGenBuffers(1, (GLuint*) &(geometry->id_normals));
	glBindBuffer(GL_ARRAY_BUFFER, geometry->id_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * geometry->num_normals * 3, geometry->normals, GL_STATIC_DRAW);

	// INDICES
	glGenBuffers(1, (GLuint*) &(geometry->id_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*geometry->num_indices, geometry->indices, GL_STATIC_DRAW);
	
	
	return ret;
}

void ModuleRenderer3D::DrawGeometry(const Geometry *geo)
{
	//ENABLES
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// VERTICES
	glBindBuffer(GL_ARRAY_BUFFER, geo->id_vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//NORMALS
	glBindBuffer(GL_ARRAY_BUFFER, geo->id_normals);
	glNormalPointer(GL_FLOAT, 0, NULL);

	//INDICES
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geo->id_indices);
	glDrawElements(GL_TRIANGLES, geo->num_indices, GL_UNSIGNED_INT, NULL);

	//DISABLES
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}