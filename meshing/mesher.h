#pragma once
#include "../am.h"
#include "../gfx/mesh.h"
#include "../utils/mat3D.h"
class am::pipeline::Mesher
{
public:
	Mesher();
	virtual am::gfx::Mesh* buildMesh(am::math::Mat3D<GridPoint>&, std::unordered_map<std::string, float>& opts) = 0;
};

