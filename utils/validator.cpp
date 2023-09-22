#include "validator.h"
#include "boost/filesystem.hpp"

using namespace am::utils;

Validator::Validator(std::string chimeraPath) {
	m_chimera = chimeraPath;

	if (!(boost::filesystem::exists("./validation"))) {
		boost::filesystem::create_directory("./validation");
	}
	std::ofstream script("./validation/algomole-area.py");
	script << "import chimera\nchimera.openModels.open(\"./validation/molecule.pdb\")\nchimera.runCommand(\"surface vertexDensity 1\")\nchimera.runCommand(\"select\")\nchimera.runCommand(\"measure area sel\")\nchimera.runCommand(\"stop now\")";
	script.close();

	std::ofstream script2("./validation/algomole-volume.py");
	script2 << "import chimera\nchimera.openModels.open(\"./validation/molecule.pdb\")\nchimera.runCommand(\"surface vertexDensity 1\")\nchimera.runCommand(\"select\")\nchimera.runCommand(\"measure volume sel\")\nchimera.runCommand(\"stop now\")";
	script2.close();
}

double Validator::areaRelativeError(std::string pdb, am::gfx::Mesh* m) {
	double exact = analyticalSurfaceArea(pdb);
	return std::abs(exact - m->surfaceArea()) / exact;
}

double Validator::analyticalSurfaceArea(std::string pdb) {
	std::ofstream molecule("./validation/molecule.pdb");
	molecule << pdb;
	molecule.close();

	std::string command = "\"" + m_chimera + "/chimera\" --nogui --script ./validation/algomole-area.py > ./validation/log.txt";
	//system(command.c_str());
	std::system(command.c_str());
	return getValue(0);
}

double Validator::volumeRelativeError(std::string pdb, am::gfx::Mesh* m) {
	double exact = analyticalVolume(pdb);
	return std::abs(exact - m->volume()) / exact;
}

double Validator::analyticalVolume(std::string pdb) {
	std::ofstream molecule("./validation/molecule.pdb");
	molecule << pdb;
	molecule.close();

	std::string command = "\"" + m_chimera + "/chimera\" --nogui --script ./validation/algomole-volume.py > ./validation/log.txt";
	std::system(command.c_str());
	return getValue(1);
}

double Validator::getValue(int what) {
	std::ifstream logFile("./validation/log.txt");
	std::string log((std::istreambuf_iterator<char>(logFile)),
		std::istreambuf_iterator<char>());
	logFile.close();
	if (what == 0) {
		std::size_t found = log.find("MSMS main surface of molecule.pdb:  area = ");
		std::size_t equalsPos = found + sizeof("MSMS main surface of molecule.pdb:  area = ") - 1;
		std::string numericPart = log.substr(equalsPos);
		return std::stod(numericPart);
	}
	else {
		std::size_t found = log.find("MSMS main surface of molecule.pdb:  volume = ");
		std::size_t equalsPos = found + sizeof("MSMS main surface of molecule.pdb:  volume = ") - 1;
		std::string numericPart = log.substr(equalsPos);
		return std::stod(numericPart);
	}

}