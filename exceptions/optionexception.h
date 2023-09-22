#pragma once

#include "../am.h"


/**
 * @brief The OptionException class represents a base exception for option-related errors.
 */
class am::pipeline::options::OptionException : public std::exception
{
public:
	/**
	 * @brief Constructor for the OptionException class.
	 *
	 * This constructor takes an error message and constructs a formatted error message
	 * prefixed with "OPTION ERROR."
	 *
	 * @param message The error message to include in the exception.
	 */
	OptionException(const std::string message) {
		errorMessage = "OPTION ERROR: " + message + "\n";
	}

	const char* what() const noexcept override {
		return errorMessage.c_str();
	}
protected:
	std::string errorMessage; /**< The formatted error message. */
	
};