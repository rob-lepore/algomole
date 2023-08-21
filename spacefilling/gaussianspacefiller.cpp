#include "gaussianspacefiller.h"
#include <iostream>
am::Mat3D<am::GridPoint> GaussianSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts)
{
	int size = opts["size"];
	am::Mat3D<am::GridPoint> volume(size, size, size, { am::bio::Atom(glm::vec3(0), ' ', 0), 0 });

	std::unordered_map<char, float> s_map;
	std::unordered_map<char, float> sigma_map;


	float rp = opts["probe_radius"] * opts["scaling_factor"];
	float ln2 = std::log(2);
	for (const auto& atom : atoms)
	{
		float r = atom.radius;
		float s_2;
		int sigma;


		if (s_map[atom.element] != 0.f) {
			s_2 = s_map[atom.element];
			sigma = sigma_map[atom.element];
		}
		else {
			float d = 2.f * r;
			s_2 = 2.f * rp * rp + 2.f * r * rp - rp * std::sqrt(4 * (r + rp) * (r + rp) - d * d);
			s_2 /= (2.f * ln2 * r * r);
			s_map[atom.element] = s_2;
			sigma = std::round(6 * std::sqrt(s_2) * r);
			sigma_map[atom.element] = sigma;
		}

		glm::vec3 c(size/2);
		c += atom.position;

		for (int x = c.x - sigma; x < c.x + sigma; x++) {
			for (int y = c.y - sigma; y < c.y + sigma; y++) {
				for (int z = c.z - sigma; z < c.z + sigma; z++) {
					if (x >= 0 && y >= 0 && z >= 0 && x < size && y < size && z < size) {
						float dist = (c.x - x) * (c.x - x) + (c.y - y) * (c.y - y) + (c.z - z) * (c.z - z);
						float eta = std::exp(-dist / (2 * s_2 * r * r) + 1 / (2 * s_2));
						volume.at(x, y, z).value += eta;
						volume.at(x, y, z).atom = am::bio::Atom(atom.position, atom.element, atom.radius, atom.chainId);
					}
				}
			}
		}
	}


	return volume;
}
