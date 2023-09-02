#pragma once
#include "../am.h"
#include <fstream>
#include <iostream>
#include "../gfx/mesh.h"




class am::utils::Validator
{
public:
	Validator(std::string chimeraPath) {
		m_chimera = chimeraPath;

		std::ofstream script("./validation/algomole-area.py");
		script << "import chimera\nchimera.openModels.open(\"./validation/molecule.pdb\")\nchimera.runCommand(\"surface\")\nchimera.runCommand(\"stop now\")";
		script.close();
	}

	double surfaceRelativeError(std::string pdb, am::gfx::Mesh* m) {
		std::ofstream molecule("./validation/molecule.pdb");
		molecule << pdb;
		molecule.close();
		
		std::string command = "\"" + m_chimera + "/chimera\" --nogui --script ./validation/algomole-area.py > ./validation/log.txt";
		system(command.c_str());
		double exact = getValue();
		return std::abs(exact - m->surfaceArea()) / exact;
	}

	double analyticalSurfaceArea(std::string pdb) {
		std::ofstream molecule("./validation/molecule.pdb");
		molecule << pdb;
		molecule.close();

		std::string command = "\"" + m_chimera + "/chimera\" --nogui --script ./validation/algomole-area.py > ./validation/log.txt";
		system(command.c_str());
		return getValue();
	}

	double volumeRelativeError(std::string pdb, am::gfx::Mesh* m) {
		std::ofstream molecule("./validation/molecule.pdb");
		molecule << pdb;
		molecule.close();
		

	}

private:
	std::string m_chimera;

	double getValue() {
		std::ifstream logFile("./validation/log.txt");
		std::string log((std::istreambuf_iterator<char>(logFile)),
			std::istreambuf_iterator<char>());
		logFile.close();
		std::size_t found = log.find("Total solvent excluded surface area = ");
		std::size_t equalsPos = found + sizeof("Total solvent excluded surface area = ") - 1;

		// Estrai la parte numerica dopo l'uguale
		std::string numericPart = log.substr(equalsPos);

		// Converte la parte numerica in un numero a virgola mobile
		return std::stod(numericPart);
	}
};