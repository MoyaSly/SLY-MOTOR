#include "MathGeoLib\MathGeoLib.h"
#include "Globals.h"

#ifndef __Geometry_H__
#define __Geometry_H__

struct Geometry
{
	// Indices
	uint id_indices = 0; // id in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;

	// Vertices
	uint id_vertices = 0; // id in VRAM
	uint num_vertices = 0;
	float3 *vertices = nullptr;

	// Normals
	uint id_normals = 0; // id in VRAM
	uint num_normals = 0;
	float3 *normals = nullptr;

};

#endif