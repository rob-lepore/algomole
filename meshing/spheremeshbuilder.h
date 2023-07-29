#pragma once

#include "meshbuilder.h"

class SphereMeshBuilder : public MeshBuilder
{
	am::gfx::Mesh* buildMesh(am::Mat3D<am::bio::Atom>&, std::unordered_map<std::string, float> opts);

};