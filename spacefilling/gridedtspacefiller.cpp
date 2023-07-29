#include "gridedtspacefiller.h"
#include "spherespacefiller.h"
#include <iostream>
#include <queue>

double euclideanDistance(const glm::vec3& p1, const glm::vec3& p2) {
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	double dz = p2.z - p1.z;
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

am::Mat3D<am::bio::Atom> GridEDTSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float> opts) {
	float scale = opts["scaling_factor"];
	float probe = opts["probe_radius"];
	
	SphereSpaceFiller filler;
	am::Mat3D<am::bio::Atom> volume = filler.buildVolume(atoms, opts);

	if (opts["surface"] == am::MS) {

		am::Mat3D<float> distanceGrid(volume.width(), volume.height(), volume.depth(), std::pow(2, 32));
		std::queue<glm::vec3> queue;

		for (int i = 0; i < volume.width(); i++) {
			for (int j = 0; j < volume.height(); j++) {
				for (int k = 0; k < volume.depth(); k++) {
					if (volume.at(i, j, k).element == ' ') {
						distanceGrid.at(i, j, k) = 0;
						queue.push({ i,j,k });
					}
				}
			}
		}

		while (!queue.empty()) {
			glm::vec3 current = queue.front();
			queue.pop();

			int dx[26] = { -1,  0, +1, -1,  0, +1, -1,  0, +1, -1,  0, +1, -1, +1, -1, 0, +1, -1,  0, +1, -1,  0, +1, -1,  0, +1 };
			int dy[26] = { -1, -1, -1,  0,  0,  0,  1,  1,  1, -1, -1, -1,  0, 0,   1, 1,  1, -1, -1, -1,  0,  0,  0,  1,  1,  1 };
			int dz[26] = { -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 0,   0, 0,  0, +1, +1, +1, +1, +1, +1, +1, +1, +1, };

			for (int i = 0; i < 26; i++) {
				int nx = current.x + dx[i];
				int ny = current.y + dy[i];
				int nz = current.z + dz[i];

				if (nx >= 0 && nx < volume.width() && ny >= 0 && ny < volume.height() && nz >= 0 && nz < volume.depth()) {
					// Calculate the distance from the current point to the neighbor
					double distance = euclideanDistance(current, glm::vec3(nx, ny, nz));
					double value = distance + distanceGrid.at(current.x, current.y, current.z);
					//std::cout << value << "\n";

					// Update the distance if it's smaller than the current value
					if (value < distanceGrid.at(nx, ny, nz)) {
						distanceGrid.at(nx, ny, nz) = value;
						queue.push(glm::vec3(nx, ny, nz));
					}
				}
			}
		}


		for (int i = 0; i < volume.width(); i++) {
			for (int j = 0; j < volume.height(); j++) {
				for (int k = 0; k < volume.depth(); k++) {
					if (distanceGrid.at(i, j, k) < probe * scale) {
						volume.at(i, j, k).element = ' ';
					}
					/* reentrant surface
					else if (euclideanDistance( volume.at(i, j, k).position, ( glm::vec3(i,j,k) - glm::vec3(opts["size"]/2) ) ) > volume.at(i, j, k).radius - probe) {
						volume.at(i, j, k).element = 'X';
					}
					*/
				}
			}
		}
	}

	return volume;
}