/*#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLoader.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#include "mmgr/mmgr.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
using namespace std;

ModuleSceneLoader::ModuleSceneLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleSceneLoader::~ModuleSceneLoader()
{}

// Called before render is available
bool ModuleSceneLoader::Init()
{
	LOG("Loading ModuleSceneLoader");
	bool ret = true;
	struct aiLogStream stream;

	// Stream log messages to Debug window
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

bool ModuleSceneLoader::Start()
{
	string t;
	//Import("/Assets/Animation/Ethan/Ethan.fbx", t);
	return true;
}

// Called before quitting or switching levels
bool ModuleSceneLoader::CleanUp()
{
	LOG("CleanUp ModuleSceneLoader");

	// detach log stream
	aiDetachAllLogStreams();

	return true;
}*/