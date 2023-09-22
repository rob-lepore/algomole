#pragma once
#include "../am.h"

/**
 * @brief The Preprocessing class represents an abstract base class for preprocessing operations on atomic data.
 */
class am::pipeline::Preprocessing {
public:
    /**
     * @brief Transforms a vector of Atom objects based on specified options.
     *
     * This method takes a vector of Atom objects and a map of options as input, and performs a preprocessing
     * transformation on the atoms according to the specified options. It returns a vector of transformed Atom objects.
     *
     * @param atoms A vector containing Atom objects to be preprocessed.
     * @param opts A map containing options as key-value pairs.
     * @return A vector of transformed Atom objects.
     */
	virtual std::vector<am::bio::Atom> transform(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) = 0;
};