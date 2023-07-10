#pragma once
#include "surfaceextractor.h"


class SurfaceExtractorBuilder
{
public:

	SurfaceExtractorBuilder& setFileParser(FileParser* fp);
	SurfaceExtractorBuilder& setPreprocessing(Preprocessing* p);
	SurfaceExtractorBuilder& SetSpaceFiller(SpaceFiller* sf);
	SurfaceExtractorBuilder& setMeshBuilder(MeshBuilder* mb);
	SurfaceExtractorBuilder& setOption(std::string key, float value);

	SurfaceExtractor build();


private:
	FileParser* m_parser;
	Preprocessing* m_pre;
	SpaceFiller* m_spacefiller;
	MeshBuilder* m_mesher;
	std::unordered_map<std::string, float> m_opts;
};
