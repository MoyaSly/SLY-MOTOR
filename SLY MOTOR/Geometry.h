#ifndef __Geometry_H__
#define __Geometry_H__

#include "Globals.h"
#include "Component.h"


struct aiMesh;
struct aiNode;
struct aiScene;

class Geometry : public Component
{
public:
	Geometry(GameObject* _object, int _id);
	~Geometry();

	// INDICES
	uint id_indices = 0; // id in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;

	// VERTICES
	uint id_vertices = 0; // id in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

	// NORMALS
	uint id_normals = 0; // id in VRAM
	uint num_normals = 0;
	float* normals = nullptr;

	//TEXTURES
	uint id_textures = 0; // id in VRAM
	uint num_textures = 0;
	float* textures = nullptr;
	bool textured = false;

	bool LoadGeo(const aiMesh* mesh, const aiScene* scene);

	bool init = false;
};

#endif