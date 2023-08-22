#pragma once
#include "../am.h"
#include "../parsing/fileparser.h"
#include "../spacefilling/spacefiller.h"
#include "../meshing/mesher.h"
#include "../preprocessing/preprocessing.h"
#include "../postprocessing/postprocessing.h"

class am::pipeline::controller::SurfaceExtractor
{

public:

	am::pipeline::controller::SurfaceExtractor(FileParser*, Preprocessing*, SpaceFiller*, Mesher*, Postprocessing*, std::unordered_map<std::string, float>);
	am::gfx::Mesh* generateSurfaceMesh(std::string file);

private:
	am::pipeline::FileParser* m_fileParser;
	am::pipeline::SpaceFiller* m_spacefiller;
	am::pipeline::Mesher* m_mesher;
	am::pipeline::Preprocessing* m_pre;
	am::pipeline::Postprocessing* m_post;
	std::unordered_map<std::string, float> m_opts;
	
};

