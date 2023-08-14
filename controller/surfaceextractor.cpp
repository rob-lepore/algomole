#include "surfaceextractor.h"
#include "../gfx/mesh.h"
#include "../utils/mat3D.h"
#include <iostream>

SurfaceExtractor::SurfaceExtractor(FileParser* fp, Preprocessing* p, SpaceFiller* sf, Mesher* mb, Postprocessing* post, std::unordered_map<std::string, float> opts) {
	m_fileParser = fp;
	m_pre = p;
	m_spacefiller = sf;
	m_mesher = mb;
	m_post = post;
	m_opts = opts;
}


am::gfx::Mesh* SurfaceExtractor::generateSurfaceMesh(std::string file) {

	//step 1
    std::vector<am::bio::Atom> parsed = m_fileParser->parse(file, m_opts);
    auto atoms = m_pre->transform(parsed, m_opts);

	//step 2
    am::Mat3D<am::GridPoint> grid = m_spacefiller->buildVolume(atoms, m_opts);

	//step 3
    am::gfx::Mesh* mesh = m_mesher->buildMesh(grid, m_opts);

	//step 4
	am::gfx::Mesh* result = m_post->transform(mesh, m_opts);
    return result;
}
