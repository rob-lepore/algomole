#pragma once
#include "../am.h"
#include "../gfx/mesh.h"
#include "../utils/mat3D.h"

/**
 * @brief The Mesher class represents a base class for meshing algorithms.
 *
 * Subclasses of Mesher implement specific meshing algorithms to generate
 * meshes from a 3D grid.
 */

class am::pipeline::Mesher
{
public:
	/**
	 * @brief Constructor for the Mesher class.
	 */
	Mesher();

    /**
     * @brief Virtual method to build a mesh from a 3D grid that subclasses must implement.
     *
     * This method is overridden by subclasses to implement specific meshing
     * algorithms. It takes a 3D grid and a map of options as input and returns
     * a pointer to the generated mesh.
     *
     * @param grid A 3D grid represented as a Mat3D of GridPoint objects.
     * @param opts A map containing options as key-value pairs.
     * @return A pointer to the generated Mesh object.
     */
	virtual am::gfx::Mesh* buildMesh(am::math::Mat3D<GridPoint>&, std::unordered_map<std::string, float>& opts) = 0;
};

