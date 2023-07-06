#include "mesh.h"
#include <iostream>

am::gfx::Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, GLenum mode) {
    this->vertices = v;
    this->indices = i;
    m_renderMode = mode;
}

am::gfx::Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<glm::vec3> n, GLenum mode) {
    this->vertices = v;
    this->indices = i;
    this->normals = n;
    m_renderMode = mode;
}

am::gfx::Mesh::Mesh() {
    this->vertices.clear();
    this->indices.clear();
    m_renderMode = GL_TRIANGLES;
}



void am::gfx::Mesh::toObjFile(std::string path) {
    std::ofstream outfile(path);
    for (am::gfx::Vertex v : vertices) {
        outfile << "v " << v.position.x << " " << v.position.y << " " << v.position.z << "\n";
    }
    for (glm::vec3 v : normals) {
        outfile << "vn " << v.x << " " << v.y << " " << v.z << "\n";
    }
    for (int i = 0; i < indices.size(); i += 3) {
        outfile << "f " << indices[i] + 1 << "//" << indices[i] + 1 << " ";
        outfile << indices[i + 1] + 1 << "//" << indices[i + 1] + 1 << " ";
        outfile << indices[i + 2] + 1 << "//" << indices[i + 2] + 1 << "\n";
    }
}

