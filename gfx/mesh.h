#pragma once
#include "../am.h"
#include <set>

namespace am{
    namespace gfx {

        class Mesh
        {

        public:
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, am::pipeline::options::RenderMode mode);
            Mesh(am::pipeline::options::RenderMode mode);
            Mesh();

            void recalculateNormals();
            void toObjFile(std::string path);

            void addVertex(Vertex v);
            void addFace(unsigned int a,unsigned int b,unsigned int c);

            const std::vector<Vertex>& getVertices();
            const std::vector<unsigned int>& getIndices();
            const am::pipeline::options::RenderMode& getRenderMode();
            std::set<unsigned int> connectedVertices(unsigned int vertex);

        private:

            std::vector<Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            std::map<unsigned int, std::set<unsigned int>> m_adjacency;

            am::pipeline::options::RenderMode m_renderMode;

        };
    }
}