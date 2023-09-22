#pragma once
#include "mesher.h"
#include <random>
#include <iostream>

/**
 * @brief The MarchingCubesMesher class is a concrete implementation of a mesher
 *        that implements the Marching Cubes algorithm.
 * 
 * Configurable options:
 *     - size: number of cells along a dimension of the grid (required)
 *     - normals: choose whether to use sharp or smooth normals (am::pipeline::options::Normals). Defaults to SMOOTH
 *     - color_mode: coloring policy (am::pipeline::options::ColorMode). Defaults to MONO
 *     - isovalue: level of the isosurface to build. It's usually set by the space filling component. Defaults to 1
 */
class am::pipeline::MarchingCubesMesher : public am::pipeline::Mesher
{
public:
    /**
     * @brief Builds a mesh from a 3D grid using the Marching Cubes algorithm.
     *
     * This method takes a 3D grid represented as a Mat3D of GridPoint objects and a map
     * of options as input. It generates a mesh using the Marching Cubes algorithm and
     * returns a pointer to the generated Mesh object.
     *
     * @param grid A 3D grid represented as a Mat3D of GridPoint objects.
     * @param opts A map containing options as key-value pairs.
     * @return A pointer to the generated Mesh object.
     */
    am::gfx::Mesh* buildMesh(am::math::Mat3D<GridPoint>& grid, std::unordered_map<std::string, float>& opts) override;

private:

    //static int edgeTable[256];
    static int triTable[256][16];

    inline glm::vec3 interpolate(const glm::vec3& first, const glm::vec3& second, float);
    inline glm::vec4 getColor(const GridPoint& a, const GridPoint& b, int colorMode, float isovalue);

    struct Vec3Hash {
        std::size_t operator()(const glm::vec3& v) const {
            return std::hash<float>()(v.x) ^ std::hash<float>()(v.y) ^ std::hash<float>()(v.z);
        }
    };

};

