#pragma once
#include "mesher.h"
#include <random>
#include <iostream>


class am::pipeline::MarchingCubesMesher : public am::pipeline::Mesher
{
public:

    am::gfx::Mesh* buildMesh(am::math::Mat3D<GridPoint>& grid, std::unordered_map<std::string, float>& opts);

private:

    static int edgeTable[256];
    static int triTable[256][16];

    inline glm::vec3 interpolate(glm::vec3 first, glm::vec3 second, float);
    inline glm::vec4 getColor(GridPoint a, GridPoint b, int colorMode, float isovalue);

    struct Vec3Hash {
        std::size_t operator()(const glm::vec3& v) const {
            return std::hash<float>()(v.x) ^ std::hash<float>()(v.y) ^ std::hash<float>()(v.z);
        }
    };

};

