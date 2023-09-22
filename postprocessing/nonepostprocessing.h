#pragma once
#include "../am.h"
#include "postprocessing.h"

/**
 * @brief The NonePostprocessing class for a placeholder postprocessing operation that does nothing.
 */
class am::pipeline::NonePostprocessing : public am::pipeline::Postprocessing
{
    /**
     * @brief Placeholder postprocessing operation that returns the input mesh unchanged.
     *
     * This method takes a Mesh object and a map of options as input. It returns the input mesh
     * unchanged, effectively performing no postprocessing transformation.
     *
     * @param mesh A pointer to the Mesh object to be transformed.
     * @param opts A map containing options as key-value pairs.
     * @return A pointer to the input Mesh object without any transformation.
     */
	am::gfx::Mesh* transform(am::gfx::Mesh* m, std::unordered_map<std::string, float>& opts) {
		return m;
	}
};