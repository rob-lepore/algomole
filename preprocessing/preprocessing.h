#pragma once
#include "../am.h"

class am::pipeline::Preprocessing {
public:
	virtual std::vector<am::bio::Atom> transform(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) = 0;
};