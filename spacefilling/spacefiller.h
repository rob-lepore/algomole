#pragma once
#include "../am.h"
#include "../utils/mat3D.h"

class SpaceFiller
{
public:

    SpaceFiller() { };
    virtual am::Mat3D<am::GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) = 0;
};

