#pragma once

#include "spacefiller.h"

class am::pipeline::GaussianSpaceFiller : public SpaceFiller
{
	virtual am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) override;
};