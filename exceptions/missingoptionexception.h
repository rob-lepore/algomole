#pragma once

#include "optionexception.h"
/**
 * @brief The MissingOptionException class represents an exception that is
 *        thrown when a required option is missing a value.
 */
class am::pipeline::options::MissingOptionException : public OptionException
{
    /**
     * @brief Constructor for the MissingOptionException class.
     *
     * This constructor takes the key of the missing option and constructs an
     * error message indicating that a it's missing a value.
     *
     * @param key The key of the missing option.
     */
public:
	MissingOptionException(const std::string key) : OptionException("Missing value for option " + key) { }
};