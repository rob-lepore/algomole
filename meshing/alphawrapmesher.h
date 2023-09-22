#pragma once

#include "../am.h"
#include "mesher.h"
/**
 * @brief The AlphaWrapMesher class represents a concrete implementation of a mesher
 *        using the Alpha-Wrap algorithm.
 * 
 * The AlphaWrapMesher class represents a concrete implementation of a mesher
 * using the Alpha-Wrap algorithm. This class requires a CGAL library installation.
 * 
 * Configurable options:
 *     - size: number of cells along a dimension of the grid (required)
 *     - relative_alpha: parameter for the CGAL function. A bigger value means a smaller alpha. Defaults to 100
 *     - relative_offset: parameter for the CGAL function. A bigger value means a smaller offset. Defaults to 500
 *     - isovalue: level of the isosurface to build. It's usually set by the space filling component. Defaults to 1
 */
class AlphaWrapMesher : public am::pipeline::Mesher
{
public:
    /**
     * @brief Builds a mesh from a 3D grid using the Alpha-Wrap algorithm.
     *
     * This method takes a 3D grid represented as a Mat3D of GridPoint objects and a map
     * of options as input. It generates a mesh using the Alpha-Wrap algorithm and
     * returns a pointer to the generated Mesh object.
     *
     * @param grid A 3D grid represented as a Mat3D of GridPoint objects.
     * @param opts A map containing options as key-value pairs.
     * @return A pointer to the generated Mesh object.
     */
	am::gfx::Mesh* buildMesh(am::math::Mat3D<am::pipeline::GridPoint>&, std::unordered_map<std::string, float>& opts) override;
};