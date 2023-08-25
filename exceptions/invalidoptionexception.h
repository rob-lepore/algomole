#pragma once

#include "../am.h"
#include "optionexception.h"

class am::pipeline::options::InvalidOptionException : public OptionException
{
public:
	InvalidOptionException(const std::string key, float value) : OptionException("Invalid value for option " + key + ": it should be set to " + std::to_string(value)) { }
};