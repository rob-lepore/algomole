#pragma once
#include "../am.h"
#include <set>

namespace am{
    namespace gfx {

        /**
         * @brief The Mesh class is an indexed faces representation of a 3D mesh.
         */
        class Mesh
        {

        public:
            /**
             * @brief Constructor for the Mesh class with vertices, indices, and rendering mode.
             *
             * @param vertices A vector of Vertex objects representing the mesh vertices.
             * @param indices A vector of unsigned integers representing the mesh indices.
             * @param mode The rendering mode of the mesh.
             */
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, am::pipeline::options::RenderMode mode = am::pipeline::options::TRIANGLES);
            /**
             * @brief Constructor for an empty mesh.
             *
             * @param mode The rendering mode of the mesh.
             */
            Mesh(am::pipeline::options::RenderMode mode);
            /**
             * @brief Constructor for an empty mesh.
             */
            Mesh();

            /**
             * @brief Recalculates the vertex normals as the average between the normals of the faces that share the vertex.
             */
            void recalculateNormals();
            /**
             * @brief Exports the mesh to an OBJ file.
             *
             * @param path The path to the OBJ file to write.
             */
            void toObjFile(std::string path);

            /**
             * @brief Adds a vertex to the mesh.
             *
             * @param v The Vertex object to add.
             */
            void addVertex(Vertex v);
            /**
             * @brief Adds a triangular face to the mesh using vertex indices.
             *
             * @param a The index of the first vertex.
             * @param b The index of the second vertex.
             * @param c The index of the third vertex.
             */
            void addFace(unsigned int a,unsigned int b,unsigned int c);

            /**
             * @brief Retrieves the vertices of the mesh.
             *
             * @return A vector containing Vertex objects.
             */
            const std::vector<Vertex>& getVertices();
            /**
             * @brief Retrieves the indices of the mesh.
             *
             * @return A vector containing the indices that describe faces.
             */
            const std::vector<unsigned int>& getIndices();
            /**
            * @brief Retrieves the rendering mode of the mesh.
            *
            * @return The rendering mode of the mesh as a RenderMode enumeration.
            */
            const am::pipeline::options::RenderMode& getRenderMode();
            /**
             * @brief Retrieves the set of connected vertices to the given vertex.
             *
             * @param vertex The index of the vertex to find connected vertices for.
             * @return A set of indices representing connected vertices.
             */
            std::set<unsigned int> connectedVertices(unsigned int vertex);
            /**
             * @brief Calculates the surface area of the mesh.
             * 
             * Calculates the surface area of the mesh as the sum of the triangular faces area. The first time this method is called,
             * the calculation is scaled by the given scaling factor. Following calls return the first calculation result.
             * 
             * @param scale A scaling factor for the surface area calculation (default is 1.0).
             * @return The surface area of the mesh.
             */
            double surfaceArea(float scale = 1.f);
            /**
             * @brief Calculates the volume of the mesh.
             *
             * Calculates the volume of the mesh. The first time this method is called,
             * the calculation is scaled by the given scaling factor. Following calls return the first calculation result.
             * Source: https://n-e-r-v-o-u-s.com/blog/?p=4415#:~:text=The%20idea%20behind%20calculating%20the,%2C0)%20to%20the%20triangle.
             * 
             * @param scale A scaling factor for the volume calculation (default is 1.0).
             * @return The volume of the mesh.
             */
            double volume(float scale = 1.f);

        private:

            std::vector<Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            std::map<unsigned int, std::set<unsigned int>> m_adjacency;
            
            double m_area = -1.;
            double m_volume = -1.;
            am::pipeline::options::RenderMode m_renderMode;

        };
    }
}