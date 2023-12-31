#include "boundingboxpreprocessing.h"
#include "../exceptions/optionexception.h"
#include "glm/gtx/string_cast.hpp"
using namespace am::pipeline;

std::vector<am::bio::Atom> BoundingBoxPreprocessing::transform(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) {
	utils::Logger log("Preprocessing");
	float boxSize, probe, surface;
	try {
		 boxSize = options::getOptionWithError(opts, "size");
		 probe = options::getOption(opts, "probe_radius", 1.4);
		 surface = options::getOption(opts, "surface", options::VDWS);
	}
	catch(options::OptionException &e) {
		throw e;
	} 
	

	// Find molecule bounding box
	glm::vec3 minValues = atoms[0].position;
	glm::vec3 maxValues = atoms[0].position;
	glm::vec3 sums = glm::vec3(0.0f);

	for (int i = 0; i < atoms.size(); i++) {
		glm::vec3 pos = atoms[i].position;
		minValues.x = std::min(minValues.x, pos.x);
		minValues.y = std::min(minValues.y, pos.y);
		minValues.z = std::min(minValues.z, pos.z);

		maxValues.x = std::max(maxValues.x, pos.x);
		maxValues.y = std::max(maxValues.y, pos.y);
		maxValues.z = std::max(maxValues.z, pos.z);

		sums += pos;
	}

	glm::vec3 diff = maxValues - minValues;
	float margin = 8.f;
	float size = std::max({ diff.x, diff.y, diff.z }) + margin;

	float scaleFactor = boxSize / size;
	opts["scaling_factor"] = scaleFactor;

	glm::vec3 centroid = (maxValues + minValues) / 2.0f;

	if (opts["log"] == options::VERBOSE)
		log.log("Scaling factor: " + std::to_string(scaleFactor) + "  Centroid: " + glm::to_string(centroid) + "  Space size: " + std::to_string(size));

	std::vector<am::bio::Atom> scaled;
	for (const auto& a : atoms) {
		float radius;
		if(surface == options::VDWS){
			radius = a.radius;
		}
		else {
			radius = a.radius + probe;
		}

		am::bio::Atom s = { (a.position - centroid) * scaleFactor, a.element, radius * scaleFactor, a.chainId };
		scaled.push_back(s);
	}

	return scaled;

}