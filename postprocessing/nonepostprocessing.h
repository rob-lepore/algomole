#pragma once
#include "../am.h"
#include "postprocessing.h"

class NonePostprocessing : public Postprocessing 
{
	am::gfx::Mesh* transform(am::gfx::Mesh* m, std::unordered_map<std::string, float>& opts) {
		return m;
	}
};