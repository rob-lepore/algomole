#pragma once
#include "../am.h"

/**
 * @brief The FileParser class represents a base class for parsing files containing molecular data.
 *
 * Subclasses of FileParser implement specific file parsing algorithms to extract data.
 */

class am::pipeline::FileParser
{
public:

    /**
     * @brief Constructor for the FileParser class.
     */
    FileParser() { };

    /**
     * @brief Virtual method to parse a file and extract molecular data.
     *
     * This method is overridden by subclasses to implement specific file parsing
     * algorithms. It takes the file content as a string and a map of options as input and returns
     * a vector containing the parsed data, represented as Atom objects.
     *
     * @param file The content of the file to be parsed.
     * @param opts A map containing options as key-value pairs.
     * @return A vector containing the parsed data as Atom objects.
     */
    virtual std::vector<am::bio::Atom> parse(std::string file, std::unordered_map<std::string, float>& opts) = 0;
    
};

