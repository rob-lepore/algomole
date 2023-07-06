#pragma once
#include "../am.h"
#include "../gfx/mesh.h"
class MeshBuilder
{
public:
	MeshBuilder();
	virtual am::gfx::Mesh* buildMesh(mat3D, std::unordered_map<std::string, float> opts) = 0;
};

