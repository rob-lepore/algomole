#include "surfaceextractor.h"
#include "../gfx/mesh.h"
#include "../utils/mat3D.h"
#include "../utils/Logger.h"

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

	Logger log("Extractor");
	//step 1
    std::vector<am::bio::Atom> parsed = m_fileParser->parse(file, m_opts);
    auto atoms = m_pre->transform(parsed, m_opts);

	//step 2
	log.startTimer();
    am::Mat3D<am::GridPoint> grid = m_spacefiller->buildVolume(atoms, m_opts);
	log.logElapsedTime("Space filling");
	//step 3
	log.startTimer();
    am::gfx::Mesh* mesh = m_mesher->buildMesh(grid, m_opts);
	log.logElapsedTime("Meshing");

	//step 4
	am::gfx::Mesh* result = m_post->transform(mesh, m_opts);
    return result;
}
