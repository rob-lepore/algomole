#pragma once

#include "../am.h"
#include "optionexception.h"

/**
 * @brief The InvalidOptionException class represents an exception that is
 *        thrown when an invalid value is provided for an option.
 */
class am::pipeline::options::InvalidOptionException : public OptionException
{
    /**
     * @brief Constructor for the InvalidOptionException class.
     *
     * This constructor takes the key and value of the option that caused the
     * exception and constructs an error message indicating that the `value` parameter
     * is the only acceptable value for the `key`.
     *
     * @param key The key of the option.
     * @param value The only acceptable value for the option.
     */
public:
	InvalidOptionException(const std::string key, float value) : OptionException("Invalid value for option " + key + ": it should be set to " + std::to_string(value)) { }
};