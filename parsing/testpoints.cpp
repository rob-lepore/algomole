#include "testpoints.h"

std::vector<am::bio::Atom> TestPoints::parse(std::string, std::unordered_map<std::string, float>) {
	
	return {
		am::bio::Atom(glm::vec3(0), 'C', am::bio::vdwRadii.find('C')->second, 'A'),
		am::bio::Atom(glm::vec3(3,0,0), 'O', am::bio::vdwRadii.find('O')->second, 'A'),

	};

}
