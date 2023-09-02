#pragma once
#include "spacefiller.h"

class NoneSpaceFiller : public am::pipeline::SpaceFiller
{
public:
    am::math::Mat3D<am::pipeline::GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);
};

