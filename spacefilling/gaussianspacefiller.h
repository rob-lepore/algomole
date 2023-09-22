#pragma once

#include "spacefiller.h"

/**
 * @brief The GaussianSpaceFiller class represents a concrete implementation of a space filler
 *        that computes the Gaussian approximation of the molecular volume.
 *
 * The GaussianSpaceFiller class represents a concrete implementation of a space filler
 * that computes the gaussian approximation of the molecular volume. The molecular surface approximation
 * is the isosurface of level 1.
 *
 * Configurable options:
 *     - size: number of cells along a dimension of the grid (required)
 *	   - scaling_factor: usually set by the preprocessing step (required)
 *     - probe_radius: radius of the probe sphere (required)
 *     - surface: must be set to VDWS
 *
 */
class am::pipeline::GaussianSpaceFiller : public SpaceFiller
{
    /**
     * @brief Builds a 3D grid discretization of the molecular volume.
     *
     * @param atoms A vector containing Atom objects.
     * @param opts A map containing options as key-value pairs.
     * @return A Mat3D object representing the filled volume.
     */
	virtual am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) override;
};