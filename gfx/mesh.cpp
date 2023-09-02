#include "mesh.h"
#include <iostream>

using namespace am::gfx;

am::gfx::Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, am::pipeline::options::RenderMode mode) {
    m_vertices.clear();
    m_indices.clear();
    m_renderMode = am::pipeline::options::TRIANGLES;
    for (auto& vert : v) {
        addVertex(vert);
    }
    for (int k = 0; k < i.size(); k+=3) {
        addFace(i[k], i[k + 1], i[k + 2]);
    }
}

am::gfx::Mesh::Mesh(am::pipeline::options::RenderMode mode) {
    m_vertices.clear();
    m_indices.clear();
    m_renderMode = mode;
}

am::gfx::Mesh::Mesh() {
    m_vertices.clear();
    m_indices.clear();
    m_renderMode = am::pipeline::options::TRIANGLES;
}

void am::gfx::Mesh::toObjFile(std::string path) {
    std::ofstream outfile(path);
    for (const am::gfx::Vertex& v : m_vertices) {
        outfile << "v " << v.position.x << " " << v.position.y << " " << v.position.z << "\n";
    }
    for (const am::gfx::Vertex& v : m_vertices) {
        outfile << "vn " << v.normal.x << " " << v.normal.y << " " << v.normal.z << "\n";
    }
    for (int i = 0; i < m_indices.size(); i += 3) {
        outfile << "f " << m_indices[i] + 1 << "//" << m_indices[i] + 1 << " ";
        outfile << m_indices[i + 1] + 1 << "//" << m_indices[i + 1] + 1 << " ";
        outfile << m_indices[i + 2] + 1 << "//" << m_indices[i + 2] + 1 << "\n";
    }
}

const std::vector<Vertex>& am::gfx::Mesh::getVertices()
{
    return m_vertices;
}

const std::vector<unsigned int>& am::gfx::Mesh::getIndices()
{
    return m_indices;
}

const am::pipeline::options::RenderMode& Mesh::getRenderMode() {
    return m_renderMode;
}


std::set<unsigned int> am::gfx::Mesh::connectedVertices(unsigned int vertex)
{
    if (m_adjacency.find(vertex) != m_adjacency.end()) {
        return m_adjacency[vertex];
        std::cout << "questo\n";
    }
    else {
        return std::set<unsigned int>();
    }
}

void am::gfx::Mesh::recalculateNormals()
{
    std::vector<glm::vec4> vertexNormals(m_vertices.size());
    vertexNormals.assign(m_vertices.size(), glm::vec4(0));
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        // Ottieni gli indici dei vertici per questa faccia.
        unsigned int vertexIndex1 = m_indices[i];
        unsigned int vertexIndex2 = m_indices[i + 1];
        unsigned int vertexIndex3 = m_indices[i + 2];

        // Ottieni le posizioni dei vertici per questa faccia.
        glm::vec3 vertex1 = glm::vec3(m_vertices[vertexIndex1].position);
        glm::vec3 vertex2 = glm::vec3(m_vertices[vertexIndex2].position);
        glm::vec3 vertex3 = glm::vec3(m_vertices[vertexIndex3].position);

        // Calcola la normale della faccia.
        glm::vec4 faceNormal = glm::vec4(glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1)),1);

        // Aggiungi la normale della faccia ai vertici corrispondenti.
        vertexNormals[vertexIndex1] += faceNormal;
        vertexNormals[vertexIndex2] += faceNormal;
        vertexNormals[vertexIndex3] += faceNormal;
    }

    for (size_t i = 0; i < m_vertices.size(); ++i) {
        m_vertices[i].normal = glm::normalize(vertexNormals[i]);
    }

}

void am::gfx::Mesh::addVertex(Vertex v)
{
    unsigned int i = m_vertices.size();
    m_vertices.push_back(v);
    m_adjacency.insert(std::make_pair(i, std::set<unsigned int>()));
    
}

void Mesh::addFace(unsigned int a, unsigned int b, unsigned int c) {
    m_indices.push_back(a);
    m_indices.push_back(b);
    m_indices.push_back(c);

    m_adjacency[a].insert({ b, c });
    m_adjacency[b].insert({ a, c });
    m_adjacency[c].insert({ a, b });

}


double Mesh::surfaceArea(float scale) {
    if (m_area < 0) {
        m_area = 0;
        for (int i = 0; i < m_indices.size(); i += 3) {
            glm::vec3 AB = m_vertices[m_indices[i + 1]].position - m_vertices[m_indices[i]].position;
            glm::vec3 AC = m_vertices[m_indices[i + 2]].position - m_vertices[m_indices[i]].position;
            glm::vec3 crossProduct = glm::cross(AB, AC);
            m_area += 0.5 * glm::length(crossProduct);
        }
        m_area /= (scale * scale);
    }
    return m_area;
}


double Mesh::volume(float scale) {
    if (m_volume < 0) {
        m_volume = 0;
        for (int i = 0; i < m_indices.size(); i += 3) {
            glm::vec3 p1 = m_vertices[m_indices[i + 0]].position;
            glm::vec3 p2 = m_vertices[m_indices[i + 1]].position;
            glm::vec3 p3 = m_vertices[m_indices[i + 2]].position;

            float v321 = p3.x * p2.y * p1.z;
            float v231 = p2.x * p3.y * p1.z;
            float v312 = p3.x * p1.y * p2.z;
            float v132 = p1.x * p3.y * p2.z;
            float v213 = p2.x * p1.y * p3.z;
            float v123 = p1.x * p2.y * p3.z;
            m_volume += (1.0f / 6.0f) * (-v321 + v231 + v312 - v132 - v213 + v123);
        }
        m_volume /= (scale * scale * scale);
    }
    return m_volume;
}