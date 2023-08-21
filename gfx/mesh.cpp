#include "mesh.h"
#include <iostream>
#include <gl/GLU.h>
#include <gl/GL.h>


am::gfx::Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, am::RenderMode mode) {
    this->vertices = v;
    this->indices = i;
    m_renderMode = mode;
}

am::gfx::Mesh::Mesh() {
    this->vertices.clear();
    this->indices.clear();
    m_renderMode = am::TRIANGLES;
}

void am::gfx::Mesh::toObjFile(std::string path) {
    std::ofstream outfile(path);
    for (const am::gfx::Vertex& v : vertices) {
        outfile << "v " << v.position.x << " " << v.position.y << " " << v.position.z << "\n";
    }
    for (const am::gfx::Vertex& v : vertices) {
        outfile << "vn " << v.normal.x << " " << v.normal.y << " " << v.normal.z << "\n";
    }
    for (int i = 0; i < indices.size(); i += 3) {
        outfile << "f " << indices[i] + 1 << "//" << indices[i] + 1 << " ";
        outfile << indices[i + 1] + 1 << "//" << indices[i + 1] + 1 << " ";
        outfile << indices[i + 2] + 1 << "//" << indices[i + 2] + 1 << "\n";
    }
}

std::set<unsigned int> am::gfx::Mesh::connectedVertices(unsigned int vertex)
{
    std::set<unsigned int> c;

    for (int i = 0; i < indices.size(); i+=3) {
        if (indices[i] == vertex || indices[i + 1] == vertex || indices[i + 2] == vertex) { // this face contains the vertex
            if (indices[i] != vertex) c.insert(indices[i]);
            if (indices[i+1] != vertex) c.insert(indices[i+1]);
            if (indices[i+2] != vertex) c.insert(indices[i+2]);
        }
    }

    return c;
}

void am::gfx::Mesh::recalculateNormals()
{
    std::vector<glm::vec4> vertexNormals(vertices.size());
    vertexNormals.assign(vertices.size(), glm::vec4(0));
    for (size_t i = 0; i < indices.size(); i += 3) {
        // Ottieni gli indici dei vertici per questa faccia.
        unsigned int vertexIndex1 = indices[i];
        unsigned int vertexIndex2 = indices[i + 1];
        unsigned int vertexIndex3 = indices[i + 2];

        // Ottieni le posizioni dei vertici per questa faccia.
        glm::vec3 vertex1 = glm::vec3(vertices[vertexIndex1].position);
        glm::vec3 vertex2 = glm::vec3(vertices[vertexIndex2].position);
        glm::vec3 vertex3 = glm::vec3(vertices[vertexIndex3].position);

        // Calcola la normale della faccia.
        glm::vec4 faceNormal = glm::vec4(glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1)),1);

        // Aggiungi la normale della faccia ai vertici corrispondenti.
        vertexNormals[vertexIndex1] += faceNormal;
        vertexNormals[vertexIndex2] += faceNormal;
        vertexNormals[vertexIndex3] += faceNormal;
    }

    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].normal = glm::normalize(vertexNormals[i]);
    }
}
