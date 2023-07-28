#pragma once
#include "fileparser.h"

class TestPoints :
    public FileParser
{
    std::vector<am::bio::Atom> parse(std::string, std::unordered_map<std::string, float>) ;

};

