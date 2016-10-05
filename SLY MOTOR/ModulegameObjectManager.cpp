#include "Globals.h"
#include "Application.h"
#include "ModuleGameObjectManager.h"
#include "Geometry.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
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
	string t;
	//Import("/Assets/Animation/Ethan/Ethan.fbx", t);
	return true;
}

update_status ModuleGameObjectManager::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleGameObjectManager::Update(float dt)
{
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
			aiMesh *ai_mesh = scene->mMeshes[i];

			// VERTICES
			body->num_vertices = ai_mesh->mNumVertices;
			body->vertices = new float3[body->num_vertices];
			memcpy(body->vertices, ai_mesh->mVertices, sizeof(float3) * body->num_vertices);

			// NORMALES
			body->num_normals = ai_mesh->mNumVertices;
			body->normals = new float3[body->num_normals];
			memcpy(body->normals, ai_mesh->mNormals, sizeof(float3) * body->num_vertices);

			// INDICES
			if (ai_mesh->HasFaces())
			{
				body->num_indices = ai_mesh->mNumFaces * 3;
				body->indices = new uint[body->num_indices];
				for (uint j = 0; j < ai_mesh->mNumFaces; ++j)
				{
					if (ai_mesh->mFaces[j].mNumIndices == 3)
					{
						memcpy(&body->indices[j * 3], ai_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}

				}
			}

			App->renderer3D->LoadGeometryBuffer(body);
			geo.push_back(body);
		}

		aiReleaseImport(scene);
	}
	else
		LOG_ME("Error loading scene %s: %s", file, aiGetErrorString());

}