#pragma once

#include "spacefiller.h"

class EDTSpaceFiller : public SpaceFiller
{
	am::Mat3D<am::GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);
};