#include "Globals.h"
#include "Geometry.h"
#include "Application.h"

#include "Assimp\include\cimport.h"
#include "Assimp\include\scene.h"
#include "Assimp\include\postprocess.h"
#include "Assimp\include\cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")


/*Geometry::Geometry(GameObject* _parent, int _id) : Component (parent, id)
{
	char* tmp;
	sprintf(tmp, "Geo", id);
	name = tmp;
	type = ComponentGeometry;
}*/

Geometry::Geometry()
{
}

Geometry::~Geometry()
{
}

