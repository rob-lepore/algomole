#include "surfaceextractor.h"
#include "../gfx/mesh.h"
#include "../utils/mat3D.h"
#include "../utils/Logger.h"

#include <iostream>

using namespace am::pipeline::controller;

SurfaceExtractor::SurfaceExtractor(FileParser* fp, Preprocessing* p, SpaceFiller* sf, Mesher* mb, Postprocessing* post, std::unordered_map<std::string, float> opts) {
	m_fileParser = fp;
	m_pre = p;
	m_spacefiller = sf;
	m_mesher = mb;
	m_post = post;
	m_opts = opts;
}


am::gfx::Mesh* SurfaceExtractor::generateSurfaceMesh(std::string file) {

	am::utils::Logger log("Extractor");
	int logmode = options::getOption(m_opts, "log", options::MINIMAL);

	try {

		//step 1
		std::vector<am::bio::Atom> parsed = m_fileParser->parse(file, m_opts);
		auto atoms = m_pre->transform(parsed, m_opts);

		//step 2
		if (logmode != options::NO) log.startTimer();
		am::math::Mat3D<GridPoint> grid = m_spacefiller->buildVolume(atoms, m_opts);
		if (logmode != options::NO) log.logElapsedTime("Space filling");
		//step 3
		if (logmode != options::NO) log.startTimer();
		am::gfx::Mesh* mesh = m_mesher->buildMesh(grid, m_opts);
		if (logmode != options::NO) log.logElapsedTime("Meshing");

		//step 4
		am::gfx::Mesh* result = m_post->transform(mesh, m_opts);
		result->surfaceArea(m_opts["scaling_factor"]);
		result->volume(m_opts["scaling_factor"]);

		//std::cout << result->volume() / (m_opts["scaling_factor"]* m_opts["scaling_factor"]* m_opts["scaling_factor"]);
		return result;
	}
	catch(std::exception &e) {
		std::cerr << e.what();
		return new am::gfx::Mesh();
	}
}
