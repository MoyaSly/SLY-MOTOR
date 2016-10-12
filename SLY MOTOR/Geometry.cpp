#include "Globals.h"
#include "Geometry.h"
#include "GameObject.h"

#include "Assimp\include\cimport.h"
#include "Assimp\include\scene.h"
#include "Assimp\include\postprocess.h"
#include "Assimp\include\cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")


Geometry::Geometry(GameObject* _parent, int _id) : Component (parent, id)
{
	char* tmp;
	sprintf(tmp, "Geo", id);
	name = tmp;
	type = ComponentGeometry;
}

Geometry::~Geometry()
{
}

bool Geometry::LoadGeo(const aiMesh* mesh, const aiScene* scene)
{
	if (init == false)
	{
		//INDEX

		glGenBuffers(1, (GLuint*) &(id_indices));
		aiFace* face = mesh->mFaces;

		num_indices = mesh->mNumFaces * 3;
		indices = new uint[num_indices];

		for (int i = 0; i < num_indices; i += 3)
		{
			if (face->mNumIndices != 3)
			{
				LOG_ME("WARNING, geometry face with != 3 indices!");
			}
			else
			{
				indices[i] = face->mIndices[0];
				indices[i + 1] = face->mIndices[1];
				indices[i + 2] = face->mIndices[2];
			}
			face++;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_indices, indices, GL_STATIC_DRAW);

		//VERTEX
		glGenBuffers(1, (GLuint*) &(id_vertices));

		num_vertices = mesh->mNumVertices;
		vertices = new float[num_vertices * 3];
		memcpy_s(vertices, sizeof(float) * num_vertices * 3, mesh->mVertices, sizeof(float) * num_vertices * 3);

		glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * 3, vertices, GL_STATIC_DRAW);

		//NORMALS

		glGenBuffers(1, (GLuint*) &(id_normals));

		num_normals = num_vertices;
		normals = new float[num_normals * 3];
		memcpy_s(normals, sizeof(float) * num_normals * 3, mesh->mNormals, sizeof(float) * num_normals * 3);

		glBindBuffer(GL_ARRAY_BUFFER, id_normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_normals * 3, normals, GL_STATIC_DRAW);
		

		//TEXTURES

		glGenBuffers(1, (GLuint*) &(id_textures));
		num_textures = num_vertices;

		textures = new float[num_textures * 2];

		aiVector3D* tmp = mesh->mTextureCoords[0];
		for (int i = 0; i < num_textures * 2; i += 2)
		{
			textures[i] = tmp->x;
			textures[i + 1] = tmp->y;
			tmp++;
		}

		glBindBuffer(GL_ARRAY_BUFFER, id_textures);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_textures * 2, textures, GL_STATIC_DRAW);


		init = true;
		return true;
	}
	return false;
}



