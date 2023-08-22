#pragma once
#include "../am.h"
class am::pipeline::FileParser
{

public:

    virtual std::vector<am::bio::Atom> parse(std::string, std::unordered_map<std::string, float>&) = 0;

    FileParser() { };


protected:
    
};

