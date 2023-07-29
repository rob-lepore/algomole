#include "spheremeshbuilder.h"
#include "../utils/Logger.h"
#include "glm/gtc/constants.hpp"

am::gfx::Mesh* SphereMeshBuilder::buildMesh(am::Mat3D<am::bio::Atom>& volume, std::unordered_map<std::string, float> opts) {
	std::vector<am::gfx::Vertex> vertices;
	std::vector<unsigned> indices;
	std::vector<glm::vec3> normals;

	glm::vec3 centro = glm::vec3(0.0);
	glm::vec3 raggio = glm::vec3(5.0);

	int Stacks = 10;  //numero di suddivisioni sull'asse y
	int Slices = 10;  // numero di suddivisioni sull'asse x
	std::cout << volume.data().size();
	//Calc The Vertices
	for (const auto& atom : volume.data()) {
		centro = atom.position;
		Logger("Mesher").log(Logger("").vec3(centro));
		raggio = glm::vec3(atom.radius);
		//Stacks= suddivisioni lungo l'asse y
		for (int i = 0; i <= Stacks; ++i) {

			float V = i / (float)Stacks;
			float phi = V * glm::pi<float>();

			// Loop Through Slices suddivisioni lungo l'asse x
			for (int j = 0; j <= Slices; ++j) {

				float U = j / (float)Slices;
				float theta = U * (glm::pi<float>() * 2);

				// Calc The Vertex Positions
				float x = centro.x + raggio.x * (cosf(theta) * sinf(phi));
				float y = centro.y + raggio.y * cosf(phi);
				float z = centro.z + raggio.z * sinf(theta) * sinf(phi);

				vertices.push_back({ glm::vec4(x, y, z,1), glm::vec4(1) });
				normals.push_back({ x,y,z });
			}
		}

		// Calc The Index Positions
		for (int i = 0; i < Slices * Stacks + Slices; ++i) {

			indices.push_back(i);
			indices.push_back(i + Slices + 1);
			indices.push_back(i + Slices);
			indices.push_back(i + Slices + 1);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
	}

	//vertices.push_back({ glm::vec4(0,0,0,1), glm::vec4(0,0,0,0)});
	return new am::gfx::Mesh(vertices, indices, normals, GL_TRIANGLES);
}
