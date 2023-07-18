#pragma once
#include "../am.h"
#include "../gfx/mesh.h"
#include "../utils/mat3D.h"
class MeshBuilder
{
public:
	MeshBuilder();
	virtual am::gfx::Mesh* buildMesh(am::Mat3D<am::bio::Atom>&, std::unordered_map<std::string, float> opts) = 0;
};

