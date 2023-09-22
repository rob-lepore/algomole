#pragma once
#include "../am.h"


/**
 * @brief The Postprocessing class represents a base class for postprocessing operations on meshes.
 *
 * Subclasses of Postprocessing implement specific postprocessing transformations
 * that can be applied to meshes.
 */

class am::pipeline::Postprocessing {
public:
    /**
     * @brief Virtual method to perform a postprocessing transformation on a mesh.
     *
     * This method is overridden by subclasses to implement specific postprocessing
     * transformations on a mesh. It takes a mesh and a map of options as input and
     * returns a pointer to the transformed mesh.
     *
     * @param mesh A pointer to the Mesh object to be transformed.
     * @param opts A map containing options as key-value pairs.
     * @return A pointer to the transformed Mesh object.
     */
	virtual am::gfx::Mesh* transform(am::gfx::Mesh* mesh, std::unordered_map<std::string, float>& opts) = 0;
};