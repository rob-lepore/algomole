#pragma once

#include "spacefiller.h"
#include <future>
/**
 * @brief The EDTSpaceFiller class represents a concrete implementation of a space filler
 *        that computes the molecular volume as the euclidian distance transform of the solvent accessible volume.
 *
 * The EDTSpaceFiller class represents a concrete implementation of a space filler
 * that sets points inside the molecular volume to 1. This algorithms only supports calculation of
 * van der Waals surface and solvent accessible surface.
 *
 * Configurable options:
 *     - size: number of cells along a dimension of the grid (required)
 *	   - scaling_factor: usually set by the preprocessing step (required)
 *     - probe_radius: radius of the probe sphere (required)
 *     - surface: type of surface to be computed (am::pipeline::options::SurfaceType) (required)
 *     - n_threads: number of threads to be used in the calculation of the temporary EDT. Defaults to 1
 *
 */
class am::pipeline::EDTSpaceFiller : public SpaceFiller
{
	/**
	 * @brief Builds a 3D grid discretization of the molecular volume.
	 *
	 * @param atoms A vector containing Atom objects.
	 * @param opts A map containing options as key-value pairs.
	 * @return A Mat3D object representing the filled volume.
	 */
	am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);

private:
	double euclideanDistance(const glm::vec3& p1, const glm::vec3& p2);

	struct Partial {
		am::math::Mat3D<float> tEDT;
		int index;
	};

	static void func(std::promise<struct Partial>&& p, am::math::Mat3D<GridPoint> volume, int zi, int zf, int index);
};