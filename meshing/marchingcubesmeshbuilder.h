#pragma once
#include "meshbuilder.h"
#include <random>
#include <iostream>


class MarchingCubesMeshBuilder : public MeshBuilder
{
public:

    am::gfx::Mesh* buildMesh(am::Mat3D<byte> grid, std::unordered_map<std::string, float> opts);

private:

    static int edgeTable[256];
    static int triTable[256][16];

    glm::vec3 interpolate(glm::vec3 first, glm::vec3 second, float, float);
    std::vector<int> reverse(int* arr);

};

