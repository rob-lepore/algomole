#pragma once
#include "../am.h"

namespace am{
    namespace gfx {

        class Mesh
        {

        public:
            Mesh(std::vector<Vertex>, std::vector<unsigned int>, GLenum);
            Mesh(std::vector<Vertex>, std::vector<unsigned int>, std::vector<glm::vec3>, GLenum);
            Mesh();

            void toObjFile(std::string path);

            //private:

            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            std::vector<glm::vec3> normals;

            unsigned int VAO;
            unsigned int VBO;
            unsigned int VBOnormali;
            unsigned int IBO;

            GLenum m_renderMode;
        };
    }
}