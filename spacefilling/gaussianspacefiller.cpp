#include "gaussianspacefiller.h"
#include "../exceptions/optionexception.h"
#include <iostream>

double distance(glm::vec3 a, glm::vec3 b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y)* (a.y - b.y) + (a.z - b.z)* (a.z - b.z);
}

am::math::Mat3D<am::pipeline::GridPoint> am::pipeline::GaussianSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts)
{
	int size;
	float rp;

	size = options::getOptionWithError(opts, "size");
	rp = options::getOptionWithError(opts, "probe_radius") * options::getOptionWithError(opts, "scaling_factor");
	options::assertOptionValue(opts, "surface", options::VDWS);
	
	am::math::Mat3D<am::pipeline::GridPoint> volume(size, size, size, { am::bio::Atom(glm::vec3(0), ' ', 0), 0 });

	std::map<char, float> s_map;
	std::map<char, float> sigma_map;

	float ln2 = std::log(2);
	for (const auto& atom : atoms)
	{
		float r = atom.radius;
		float s_2;
		int sigma;


		if (s_map.find(atom.element) != s_map.end()){
			s_2 = s_map[atom.element];
			sigma = sigma_map[atom.element];
		}
		else {
			float d = 2.f * r;
			s_2 = 2.f * rp * rp + 2.f * r * rp - rp * std::sqrt(4 * (r + rp) * (r + rp) - d * d);
			s_2 /= (2.f * ln2 * r * r);
			s_map[atom.element] = s_2;
			sigma = std::round(4.5 * std::sqrt(s_2) * r);
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

						glm::vec3 point = { x,y,z };
						if (distance(glm::vec3(x, y, z), volume.at(x, y, z).atom.position) > distance(glm::vec3(x, y, z), c) || volume.at(x, y, z).atom.element == ' ')
							volume.at(x, y, z).atom = am::bio::Atom(c, atom.element, atom.radius, atom.chainId);
					}
				}
			}
		}
	}


	opts["isovalue"] = 1.f;

	return volume;
}
