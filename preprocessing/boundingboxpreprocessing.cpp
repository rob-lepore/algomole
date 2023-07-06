#include "boundingboxpreprocessing.h"

std::vector<am::bio::Atom> BoundingBoxPreprocessing::transform(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float> opts) {
	Logger log("Preprocessing");

	float boxSize = opts["size"];

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
	float margin = 8.0f;
	float size = std::max({ diff.x, diff.y, diff.z }) + margin;

	float scaleFactor = boxSize / size;
	glm::vec3 centroid = (maxValues + minValues) / 2.0f;//sums / (float) atoms.size();

	log.log("Scaling factor: " + std::to_string(scaleFactor) + "  Centroid: " + log.vec3(centroid) + "  Space size: " + std::to_string(size));


	std::vector<am::bio::Atom> scaled;
	for (auto a : atoms) {
		am::bio::Atom s = { (a.position - centroid) * scaleFactor, a.element, a.radius * scaleFactor };
		scaled.push_back(s);
	}

	return scaled;

}