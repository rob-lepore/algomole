#pragma once
#include "../am.h"
class FileParser
{

public:

    virtual std::vector<am::bio::Atom> parse(std::string, std::unordered_map<std::string, float>&) = 0;

    FileParser() { };


protected:
    
};

