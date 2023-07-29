#include "nonespacefiller.h"
#include "../utils/Logger.h"
am::Mat3D<am::bio::Atom> NoneSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float> opts) {
	am::Mat3D<am::bio::Atom> volume(atoms.size(), 1, 1, am::bio::Atom());

	int i = 0;
	for (auto atom : atoms) {
		volume.at(i, 0, 0) = atom;
		Logger("Spacer").log(Logger("").vec3(volume.at(i,0,0).position));
		i++;
	}
	return volume;
}