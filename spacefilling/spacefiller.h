#pragma once
#include "../am.h"

class SpaceFiller
{
public:

    SpaceFiller() { };
    virtual mat3D buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float> opts) = 0;
};

