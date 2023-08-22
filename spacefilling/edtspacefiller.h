#pragma once

#include "spacefiller.h"
#include <future>

class am::pipeline::EDTSpaceFiller : public SpaceFiller
{
	am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);

private:
	double euclideanDistance(const glm::vec3& p1, const glm::vec3& p2);

	struct Partial {
		am::math::Mat3D<float> tEDT;
		int index;
	};

	static void func(std::promise<struct Partial>&& p, am::math::Mat3D<GridPoint> volume, int zi, int zf, int index);
};