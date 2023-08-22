#pragma once
#include "../am.h"
#include "../utils/mat3D.h"

class am::pipeline::SpaceFiller
{
public:

    SpaceFiller() { };
    virtual am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) = 0;
};

