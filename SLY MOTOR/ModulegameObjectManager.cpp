#include "Globals.h"
#include "Application.h"
#include "ModuleGameObjectManager.h"
#include "Geometry.h"

#include <Windows.h>
#include "Glew/include/glew.h" // extension lib
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "Devil\include\ilu.h"
#include "Devil\include\ilut.h"

#pragma comment(lib, "Devil/libx86/DevIL.lib")
#pragma comment(lib, "Devil/libx86/ILU.lib")
#pragma comment(lib, "Devil/libx86/ILUT.lib")
using namespace std;

ModuleGameObjectManager::ModuleGameObjectManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleGameObjectManager::~ModuleGameObjectManager()
{
}

bool ModuleGameObjectManager::Init()
{
	bool ret = true;
	struct aiLogStream stream;

	// Stream log messages to Debug window
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

bool ModuleGameObjectManager::Start()
{
	return true;
}

update_status ModuleGameObjectManager::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleGameObjectManager::Update(float dt)
{
	std::vector<Geometry*>::iterator it = geo.begin();

	while (it != geo.end())
	{
		App->renderer3D->DrawGeometry((*it));
		it++;
	}
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleGameObjectManager::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting or switching levels
bool ModuleGameObjectManager::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	return true;
}

/*GameObject* ModuleGameObjectManager::CreateNewGameObject(string name, GameObject* parent = NULL)
{

}*/

void ModuleGameObjectManager::LoadGeometry(const char *file)
{
	const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// For each mesh...
		for (uint i = 0; i < scene->mNumMeshes; ++i)
		{
			Geometry *body = new Geometry();
			aiMesh *new_mesh = scene->mMeshes[i];

			// VERTICES
			body->num_vertices = new_mesh->mNumVertices;
			body->vertices = new float3[body->num_vertices];
			memcpy(body->vertices, new_mesh->mVertices, sizeof(float3) * body->num_vertices);
			LOG_ME("New mesh with %d vertices", body->num_vertices);

			// NORMALES
			body->num_normals = new_mesh->mNumVertices;
			body->normals = new float3[body->num_normals];
			memcpy(body->normals, new_mesh->mNormals, sizeof(float3) * body->num_vertices);
			LOG_ME("New mesh with %d normals", body->num_vertices);

			// INDICES
			if (new_mesh->HasFaces())
			{
				body->num_indices = new_mesh->mNumFaces * 3;
				body->indices = new uint[body->num_indices];
				for (uint j = 0; j < new_mesh->mNumFaces; ++j)
				{
					if (new_mesh->mFaces[j].mNumIndices != 3)
					{
						LOG_ME("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&body->indices[j * 3], new_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			App->renderer3D->LoadGeometryBuffer(body);
			geo.push_back(body);
		}

		aiReleaseImport(scene);
	}
	else
		LOG_ME("Error loading scene %s", file);

}
