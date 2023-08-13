#pragma once
#include "../am.h"

class Postprocessing {
public:
	virtual am::gfx::Mesh* transform(am::gfx::Mesh*, std::unordered_map<std::string, float>& opts) = 0;
};