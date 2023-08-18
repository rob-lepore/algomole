#pragma once

#include "mesher.h"

class PointsMesher : public Mesher
{
	virtual am::gfx::Mesh* buildMesh(am::Mat3D<am::GridPoint>& volume, std::unordered_map<std::string, float>& opts) override;
};