#pragma once
#include "../am.h"
#include <set>

namespace am{
    namespace gfx {

        class Mesh
        {

        public:
            Mesh(std::vector<Vertex>, std::vector<unsigned int>, am::RenderMode);
            Mesh();

            std::set<unsigned int> connectedVertices(unsigned int vertex);
            void recalculateNormals();
            void toObjFile(std::string path);


            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            am::RenderMode m_renderMode;

        };
    }
}