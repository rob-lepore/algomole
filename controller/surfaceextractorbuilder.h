#pragma once
#include "surfaceextractor.h"


class am::pipeline::controller::SurfaceExtractorBuilder
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
	am::pipeline::FileParser* m_parser;
	am::pipeline::Preprocessing* m_pre;
	am::pipeline::SpaceFiller* m_spacefiller;
	am::pipeline::Mesher* m_mesher;
	am::pipeline::Postprocessing* m_post;
	std::unordered_map<std::string, float> m_opts;
};

