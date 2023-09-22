#pragma once
#include "../am.h"
#include "../utils/mat3D.h"
/**
* @brief The SpaceFiller class represents a base class for space filling algorithms.
*
* Subclasses of SpaceFiller implement specific algorithms for filling 3D space with
* grid points based on given vector of atoms.
*/
class am::pipeline::SpaceFiller
{
public:

    /**
     * @brief Constructor for the SpaceFiller class.
     */
    SpaceFiller() { };

    /**
    * @brief Virtual method to build a 3D grid discretization of space filled with grid points 
    * based on atoms' coordinates.
    * 
    * This method is overridden by subclasses to implement specific algorithms for
    * discretizing space with a 3D grid based on a vector of atoms.
    *
    * @param atoms A vector containing Atom objects that describe the molecule.
    * @param opts A map containing options as key-value pairs.
    * @return A Mat3D object representing the filled 3D volume with grid points.
    */
    virtual am::math::Mat3D<GridPoint> buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) = 0;
};

