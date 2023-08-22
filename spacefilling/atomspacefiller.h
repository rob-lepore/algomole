#pragma once
#include "spacefiller.h"

class am::pipeline::AtomSpaceFiller : public SpaceFiller
{
public:
	am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);

private:
	float dist2(glm::vec3 a, glm::vec3 b);
	std::vector<glm::vec3> getPoints(glm::vec3 center, float r);

};