#include "surfaceextractorbuilder.h"

SurfaceExtractorBuilder& SurfaceExtractorBuilder::setFileParser(FileParser* fp) {
	m_parser = fp;
	return *this;
}
SurfaceExtractorBuilder& SurfaceExtractorBuilder::SetSpaceFiller(SpaceFiller* sf) {
	m_spacefiller = sf;
	return *this;
}
SurfaceExtractorBuilder& SurfaceExtractorBuilder::setMeshBuilder(MeshBuilder* mb) {
	m_mesher = mb;
	return *this;
}
SurfaceExtractorBuilder& SurfaceExtractorBuilder::setPreprocessing(Preprocessing* p) {
	m_pre = p;
	return *this;
}

SurfaceExtractorBuilder& SurfaceExtractorBuilder::setOption(std::string key, float value) {
	m_opts[key] = value;
	return *this;
}


SurfaceExtractor SurfaceExtractorBuilder::build() {
	SurfaceExtractor se(m_parser, m_pre, m_spacefiller, m_mesher, m_opts);
	return se;
};