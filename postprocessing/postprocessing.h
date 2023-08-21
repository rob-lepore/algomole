#pragma once
#include "../am.h"

class Postprocessing {
public:
	virtual am::gfx::Mesh* transform(am::gfx::Mesh* mesh, std::unordered_map<std::string, float>& opts) = 0;
};