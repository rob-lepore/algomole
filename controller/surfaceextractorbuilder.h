#pragma once
#include "surfaceextractor.h"


class SurfaceExtractorBuilder
{
public:

	SurfaceExtractorBuilder& setFileParser(FileParser* fp);
	SurfaceExtractorBuilder& setPreprocessing(Preprocessing* p);
	SurfaceExtractorBuilder& setSpaceFiller(SpaceFiller* sf);
	SurfaceExtractorBuilder& setMeshBuilder(Mesher* mb);
	SurfaceExtractorBuilder& setPostprocessing(Postprocessing* p);
	SurfaceExtractorBuilder& setOption(std::string key, float value);

	SurfaceExtractor build();


private:
	FileParser* m_parser;
	Preprocessing* m_pre;
	SpaceFiller* m_spacefiller;
	Mesher* m_mesher;
	Postprocessing* m_post;
	std::unordered_map<std::string, float> m_opts;
};

