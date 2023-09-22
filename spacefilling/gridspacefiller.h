#pragma once
#include "../am.h"
#include "spacefiller.h"

/**
 * @brief The GridSpaceFiller class represents a concrete implementation of a space filler
 *        that sets points inside the molecular volume to 1.
 *
 * The GridSpaceFiller class represents a concrete implementation of a space filler
 * that sets points inside the molecular volume to 1. This algorithms only supports calculation of
 * van der Waals surface and solvent accessible surface.
 *
 * Configurable options:
 *     - size: number of cells along a dimension of the grid (required)
 *
 */
class am::pipeline::GridSpaceFiller : public SpaceFiller
{
public:
    /**
     * @brief Builds a 3D grid discretization of the van der Waals volume or the solvent accessible volume.
     *
     * @param atoms A vector containing Atom objects.
     * @param opts A map containing options as key-value pairs.
     * @return A Mat3D object representing the filled volume.
     */
	am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);

private:

    float dist2(glm::vec4 a, glm::vec4 b);

};

