#pragma once
#include "../am.h"

class Postprocessing {
public:
	virtual am::gfx::Mesh* transform(am::gfx::Mesh*) = 0;
};