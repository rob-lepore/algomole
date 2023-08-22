#pragma once
#include "../am.h"
#include "preprocessing.h"
#include "../utils/Logger.h"

class am::pipeline::BoundingBoxPreprocessing : public am::pipeline::Preprocessing
{
public:
	std::vector<am::bio::Atom> transform(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts);

};

