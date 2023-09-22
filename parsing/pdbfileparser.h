#pragma once
#include "../am.h"
#include "fileparser.h"
#include "../utils/Logger.h"

/**
 * @brief The PdbFileParser class represents a concrete implementation of a file parser
 *        specifically designed for parsing PDB (Protein Data Bank) files.
 */
class am::pipeline::PdbFileParser : public am::pipeline::FileParser
{
public:
    /**
     * @brief Parses a PDB file and extracts a vector of Atom objects.
     *
     * This method takes a PDB file content in a string and a map of options as input. It parses
     * the PDB file and returns a vector containing the extracted Atom objects.
     *
     * @param file Content of the PDB file to be parsed.
     * @param opts A map containing options as key-value pairs.
     * @return A vector containing the parsed Atom objects.
     */
    std::vector<am::bio::Atom> parse(std::string file, std::unordered_map<std::string, float>& opts);

private:
    bool parseLine(std::string line, am::bio::Atom* atom);
};

