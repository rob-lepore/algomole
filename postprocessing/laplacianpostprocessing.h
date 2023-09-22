#pragma once

#include "postprocessing.h"

/**
 * @brief The LaplacianPostprocessing class represents a concrete implementation of a postprocessing
 *        operation based on the Laplacian smoothing algorithm.
 * 
 * Configurable options:
 *     - normals: choose whether to use sharp or smooth normals (am::pipeline::options::Normals). Must be set to SMOOTH
 */
class am::pipeline::LaplacianPostprocessing : public am::pipeline::Postprocessing
{
    /**
     * @brief Transforms a mesh using Laplacian smoothing.
     *
     * This method takes a Mesh object and a map of options as input. It performs
     * a Laplacian smoothing postprocessing operation on the mesh and returns a pointer
     * to the transformed Mesh object.
     *
     * @param mesh A pointer to the Mesh object to be transformed.
     * @param opts A map containing options as key-value pairs.
     * @return A pointer to the transformed Mesh object.
     */
	am::gfx::Mesh* transform(am::gfx::Mesh* mesh, std::unordered_map<std::string, float>& opts) override;
};