#include "Globals.h"
#include "Application.h"
#include "ModuleGameObjectManager.h"
#include "Geometry.h"

#include <Windows.h>
#include "Glew/include/glew.h" // extension lib
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Devil\include\il.h"
#include "Devil\include\ilu.h"
#include "Devil\include\ilut.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment(lib, "Devil/libx86/DevIL.lib")
#pragma comment(lib, "Devil/libx86/ILU.lib")
#pragma comment(lib, "Devil/libx86/ILUT.lib")

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

	for (int i = 0; i < CHECKERS_HEIGHT; i++)
	{
		for (int j = 0; j < CHECKERS_WIDTH; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	return ret;
}

bool ModuleGameObjectManager::Start()
{
	//Generating checker texture

	texture_id = App->game_object_manager->LoadIMG("C:/Users/MIQUEL/Documents/GitHub/SLY-MOTOR/SLY MOTOR/Lenna.png");

	int a = 0;
	GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	glBindTexture(GL_TEXTURE_2D, 0);
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

			uint UV_index = 0;
			if (new_mesh->HasTextureCoords(UV_index))
			{
				body->num_textures = new_mesh->mNumVertices;
				body->textures = new float2[body->num_textures];
				memcpy(body->textures, new_mesh->mTextureCoords[UV_index], sizeof(float2) * body->num_textures);
			}

			App->renderer3D->LoadGeometryBuffer(body);
			geo.push_back(body);
		}

		aiReleaseImport(scene);
	}
	else
		LOG_ME("Error loading scene %s", file);

}

uint ModuleGameObjectManager::LoadIMG(char *path)
{
	uint ret = 10;
	//ret = ilutGLLoadImage(path);
	return ret;
}