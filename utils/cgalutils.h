#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include "../gfx/mesh.h"

class am::utils::CgalUtils
{
public:
	static am::gfx::Mesh* convertFromCGALMesh(CGAL::Surface_mesh<CGAL::Exact_predicates_inexact_constructions_kernel::Point_3> m) {
		am::gfx::Mesh* mesh = new am::gfx::Mesh();
		for (const auto& vd : m.vertices()) {
			auto p = m.point(vd);
			mesh->addVertex(am::gfx::Vertex({ p.x(), p.y(), p.z(),1 }, { 0, 1, 0.3, 1 }));
		}
		for (const auto& fd : m.faces()) {
			std::vector<int> inds;
			for (const auto& vd : CGAL::vertices_around_face(m.halfedge(fd), m)) {
				inds.push_back(vd.idx());
			}
			assert(inds.size() == 3);
			mesh->addFace(inds[0], inds[1], inds[2]);
		}
		mesh->recalculateNormals();

		return mesh;
	}

};

