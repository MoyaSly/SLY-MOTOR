#ifndef __Geometry_H__
#define __Geometry_H__

#include "MathGeoLib\MathGeoLib.h"
#include "Globals.h"
#include "Component.h"


struct aiMesh;
struct aiNode;
struct aiScene;

class Geometry //: public Component
{
public:
	//Geometry(GameObject* parent, int id);
	Geometry();
	~Geometry();

	// INDICES
	uint id_indices = 0; // id in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;

	// VERTICES
	uint id_vertices = 0; // id in VRAM
	uint num_vertices = 0;
	float3 *vertices = nullptr;

	// NORMALS
	uint id_normals = 0; // id in VRAM
	uint num_normals = 0;
	float3 *normals = nullptr;

	uint id_textures = 0; // id in VRAM
	uint num_textures = 0;
	float2 *textures = nullptr;


};

#endif