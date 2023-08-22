#pragma once

#include "postprocessing.h"

class am::pipeline::LaplacianPostprocessing : public am::pipeline::Postprocessing
{
	am::gfx::Mesh* transform(am::gfx::Mesh* mesh, std::unordered_map<std::string, float>& opts) override;
};