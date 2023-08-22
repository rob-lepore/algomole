#include "laplacianpostprocessing.h"
#include "../gfx/mesh.h"

am::gfx::Mesh* am::pipeline::LaplacianPostprocessing::transform(am::gfx::Mesh* mesh, std::unordered_map<std::string, float>& opts)
{
	std::vector<am::gfx::Vertex> vertices = mesh->vertices;
	for (int i = 0; i < vertices.size(); i++) {
		am::gfx::Vertex current = vertices[i];
		std::set<unsigned int> connected = mesh->connectedVertices(i);
		glm::vec4 newPosition(0.f, 0.f, 0.f, 1.f);

		for (unsigned int index : connected) {
			newPosition += vertices[index].position;
		}
		newPosition /= connected.size();
		vertices[i].position = current.position + 1.f * (newPosition - current.position);
	}
	mesh->vertices = vertices;
	
	mesh->recalculateNormals();

	return mesh;
}