#pragma once
#include "spacefiller.h"

class SphereSpaceFiller : public SpaceFiller 
{
public:
	am::Mat3D<am::bio::Atom> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float> opts);
};