#pragma once

#include "optionexception.h"

class am::pipeline::options::MissingOptionException : public OptionException
{
public:
	MissingOptionException(const std::string key) : OptionException("Missing value for option " + key) { }
};