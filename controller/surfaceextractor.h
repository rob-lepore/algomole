#pragma once
#include "../am.h"
#include "../parsing/fileparser.h"
#include "../spacefilling/spacefiller.h"
#include "../meshing/meshbuilder.h"
#include "../preprocessing/preprocessing.h"

class SurfaceExtractor
{

public:

	SurfaceExtractor(FileParser*, Preprocessing*, SpaceFiller*, MeshBuilder*, std::unordered_map<std::string, float>);
	am::gfx::Mesh* generateSurfaceMesh(std::string file);

private:
	FileParser* m_fileParser;
	SpaceFiller* m_volumeExtractor;
	MeshBuilder* m_mesher;
	Preprocessing* m_pre;
	std::unordered_map<std::string, float> m_opts;
	
};

