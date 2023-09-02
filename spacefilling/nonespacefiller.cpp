#include "nonespacefiller.h"
#include <iostream>
am::math::Mat3D<am::pipeline::GridPoint> NoneSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts)
{
	am::math::Mat3D<am::pipeline::GridPoint> list(atoms.size(), 1, 1);
	int i = 0;
	for (const auto& a : atoms)
	{

		list.at(i, 0, 0) = { am::bio::Atom(a.position, a.element, a.radius, a.chainId), 1.f };
		//std::cout << list.value << "\n";
		i++;

	}
	return list;
}
