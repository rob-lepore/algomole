#pragma once

#include "postprocessing.h"

class LaplacianPostprocessing : public Postprocessing
{
	am::gfx::Mesh* transform(am::gfx::Mesh* mesh, std::unordered_map<std::string, float>& opts) override;
};