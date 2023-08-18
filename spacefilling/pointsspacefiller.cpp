#include "pointsspacefiller.h"
#include <iostream>

am::Mat3D<am::GridPoint> PointsSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts)
{
	int size = opts["size"];
	am::Mat3D<am::GridPoint> volume(size, size, size, { am::bio::Atom(glm::vec3(0), ' ', 0), 0 });
	for (const auto& atom : atoms) {
		int x_centro = size / 2 + atom.position.x;
		int y_centro = size / 2 + atom.position.y;
		int z_centro = size / 2 + atom.position.z;
		float raggio = atom.radius;
		volume.at(x_centro, y_centro, z_centro).atom = am::bio::Atom(atom.position, atom.element, raggio);
		volume.at(x_centro, y_centro, z_centro).value = 1;
	}

	return volume;
}
