#pragma once
#include "spacefiller.h"

/**
 * @brief The AtomSpaceFiller class represents a concrete implementation of a space filler
 *        that sets points inside the molecular volume to 1.
 * 
 * The AtomSpaceFiller class represents a concrete implementation of a space filler
 * that sets points inside the molecular volume to 1. This algorithms only supports calculation of
 * van der Waals surface and solvent accessible surface.
 * 
 * Configurable options:
 *     - size: number of cells along a dimension of the grid (required)
 * 
 */
class am::pipeline::AtomSpaceFiller : public SpaceFiller
{
public:
    /**
     * @brief Builds a 3D grid discretization of the van der Waals volume or the solvent accessible volume.
     *
     * @param atoms A vector containing Atom objects.
     * @param opts A map containing options as key-value pairs.
     * @return A Mat3D object representing the filled volume.
     */
	am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) override;

private:
	float dist2(glm::vec3 a, glm::vec3 b);
	std::vector<glm::vec3> getPoints(glm::vec3 center, float r);

};