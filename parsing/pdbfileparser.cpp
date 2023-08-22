#include "pdbfileparser.h"
#include <string>

using namespace am::pipeline;

std::vector<am::bio::Atom> PdbFileParser::parse(std::string file, std::unordered_map<std::string, float>& opts) {
    std::string line;
    std::vector<am::bio::Atom> atoms;

    for (const auto& c : file) {
        if (c != '\n') {
            line += c;
        }
        else {
            am::bio::Atom atom;
            if (parseLine(line, &atom))
                atoms.push_back(atom);
            line.clear();

        }
    }
    if (!line.empty()) {
        am::bio::Atom atom;
        if (parseLine(line, &atom))
            atoms.push_back(atom);
    }

    am::utils::Logger log("Parser");
    log.log("# of atoms: " + std::to_string(atoms.size()));
    return atoms;
}

bool PdbFileParser::parseLine(std::string line, am::bio::Atom* atom) {
    if (line.substr(0, 4) == "ATOM") {

        float X = std::stod(line.substr(30, 8));
        float Y = std::stod(line.substr(38, 8));
        float Z = std::stod(line.substr(46, 8));

        //std::cout << X << " " << Y << " " << Z << "\n";
        std::string element = line.substr(13, 2);
        char chain = line[21];

        char e;
        if (element == "Si") e = 'X';
        if (element == "Al") e = 'Y';
        else e = element[0];

        atom->element = line[13];
        atom->position = {
            X, Y, Z
        };
        atom->radius = am::bio::vdwRadii.find(atom->element)->second;
        atom->chainId = chain;
        return true;
    }
    return false;
}