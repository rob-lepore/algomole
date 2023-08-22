#pragma once
#include "../am.h"
#include "fileparser.h"
#include "../utils/Logger.h"
class am::pipeline::PdbFileParser : public am::pipeline::FileParser
{
public:
    std::vector<am::bio::Atom> parse(std::string file, std::unordered_map<std::string, float>&);

private:
    bool parseLine(std::string line, am::bio::Atom* atom);
};

