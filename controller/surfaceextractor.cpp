#include "surfaceextractor.h"
#include "../gfx/mesh.h"

SurfaceExtractor::SurfaceExtractor(FileParser* fp, Preprocessing* p, SpaceFiller* vb, MeshBuilder* mb, std::unordered_map<std::string, float> opts) {
	m_fileParser = fp;
	m_pre = p;
	m_volumeExtractor = vb;
	m_mesher = mb;
	m_opts = opts;
}


am::gfx::Mesh* SurfaceExtractor::generateSurfaceMesh(std::string file) {

	//step 1
    std::vector<am::bio::Atom> parsed = m_fileParser->parse(file, m_opts);
    auto atoms = m_pre->transform(parsed, m_opts);

	//step 2
    mat3D grid = m_volumeExtractor->buildVolume(atoms, m_opts);

	//step 3
    am::gfx::Mesh* mesh = m_mesher->buildMesh(grid, m_opts);
    return mesh;
}
