#pragma once
#include "../am.h"
#include "preprocessing.h"
#include "../utils/Logger.h"

/**
 * @brief The BoundingBoxPreprocessing class represents a preprocessing operation to move and scale atoms inside a bounding box.
 * 
 * Configurable options:
 *     - size: number of cells along a dimension of the grid (required)
 *     - probe_radius: radius of the probe sphere. Defaults to 1.4
 *     - surface: type of surface to be computed (am::pipeline::options::SurfaceType). Defaults to VDWS
 */
class am::pipeline::BoundingBoxPreprocessing : public am::pipeline::Preprocessing
{
public:
    /**
     * @brief Transforms a vector of Atom objects by moving and scaling atoms outside a bounding box of a given size.
     *
     * This method takes a vector of Atom objects and a map of options as input. It applies a preprocessing operation
     * to move and scale atoms inside a bounding box, based on the options provided. The transformed
     * Atom objects are returned in a new vector.
     *
     * @param atoms A vector containing Atom objects to be preprocessed.
     * @param opts A map containing options as key-value pairs, including bounding box parameters.
     * @return A vector of Atom objects after preprocessing.
     * 
     */
	std::vector<am::bio::Atom> transform(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);

};

