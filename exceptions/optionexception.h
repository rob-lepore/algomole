#pragma once

#include "../am.h"

class am::pipeline::options::OptionException : public std::exception
{
public:
	OptionException(const std::string message) {
		errorMessage = "OPTION ERROR: " + message + "\n";
	}

	const char* what() const noexcept override {
		return errorMessage.c_str();
	}
protected:
	std::string errorMessage;
	
};