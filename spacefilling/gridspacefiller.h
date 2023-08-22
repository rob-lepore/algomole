#pragma once
#include "../am.h"
#include "spacefiller.h"


class am::pipeline::GridSpaceFiller : public SpaceFiller
{
public:

	am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);

private:

    float dist2(glm::vec4 a, glm::vec4 b);

};

