#include "pointsmesher.h"
#include <iostream>

am::gfx::Mesh* PointsMesher::buildMesh(am::Mat3D<am::GridPoint>& volume, std::unordered_map<std::string, float>& opts)
{
    std::vector<am::gfx::Vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<glm::vec3> normals;
    int i = 0;


    for (int x = 0; x < volume.width(); x++) {
        for (int y = 0; y < volume.height(); y++) {
            for (int z = 0; z < volume.depth(); z++) {
                if (volume.at(x, y, z).value == 1) {
                    vertices.push_back(am::gfx::Vertex(glm::vec4(volume.at(x,y,z).atom.position, 1), glm::vec4(0)));
                    indices.push_back(i);
                    normals.push_back(glm::vec3(0));
                    i++;
                }
            }
        }
    }

    std::cout << vertices.size() << " " << indices.size() << " " << i << "\n";

    return new am::gfx::Mesh(vertices, indices, normals, GL_POINTS);

}
