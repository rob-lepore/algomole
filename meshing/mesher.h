#pragma once
#include "../am.h"
#include "../gfx/mesh.h"
#include "../utils/mat3D.h"
class Mesher
{
public:
	Mesher();
	virtual am::gfx::Mesh* buildMesh(am::Mat3D<am::GridPoint>&, std::unordered_map<std::string, float>& opts) = 0;
};

