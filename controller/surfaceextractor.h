#pragma once
#include "../am.h"
#include "../parsing/fileparser.h"
#include "../spacefilling/spacefiller.h"
#include "../meshing/mesher.h"
#include "../preprocessing/preprocessing.h"
#include "../postprocessing/postprocessing.h"

class SurfaceExtractor
{

public:

	SurfaceExtractor(FileParser*, Preprocessing*, SpaceFiller*, Mesher*, Postprocessing*, std::unordered_map<std::string, float>);
	am::gfx::Mesh* generateSurfaceMesh(std::string file);

private:
	FileParser* m_fileParser;
	SpaceFiller* m_spacefiller;
	Mesher* m_mesher;
	Preprocessing* m_pre;
	Postprocessing* m_post;
	std::unordered_map<std::string, float> m_opts;
	
};

