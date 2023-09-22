#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include "../gfx/mesh.h"
/**
 * @brief The CgalUtils class provides utility functions for working with CGAL data structures.
 */
class am::utils::CgalUtils
{
public:
    /**
     * @brief Converts a CGAL Surface_mesh to an AlgoMole Mesh.
     *
     * This static method takes a CGAL Surface_mesh as input and converts it into
     * an AlgoMole Mesh.
     *
     * @param m The CGAL Surface_mesh to convert.
     * @return A pointer to the converted AM Graphics Mesh.
     */
	static am::gfx::Mesh* convertFromCGALMesh(CGAL::Surface_mesh<CGAL::Exact_predicates_inexact_constructions_kernel::Point_3> m);

};

