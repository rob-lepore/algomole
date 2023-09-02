#pragma once

#include "../am.h"
#include "mesher.h"

class AlphaWrapMesher : public am::pipeline::Mesher
{
public:
	am::gfx::Mesh* buildMesh(am::math::Mat3D<am::pipeline::GridPoint>&, std::unordered_map<std::string, float>& opts) override;
};