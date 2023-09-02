#pragma once

#include "./surfaceextractorbuilder.h"

class am::pipeline::controller::Director {
public:
	enum Type {GAUSSIAN, EDT};

	Director() {};
	void make(SurfaceExtractorBuilder& builder, Type t);
};