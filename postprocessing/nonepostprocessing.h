#pragma once
#include "../am.h"
#include "postprocessing.h"

class NonePostprocessing : public Postprocessing 
{
	am::gfx::Mesh* transform(am::gfx::Mesh* m) {
		return m;
	}
};