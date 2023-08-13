#include "testpoints.h"

std::vector<am::bio::Atom> TestPoints::parse(std::string, std::unordered_map<std::string, float>& opts) {
	
	return {
		am::bio::Atom(glm::vec3(0), 'O', am::bio::vdwRadii.find('O')->second, 'C'),
		am::bio::Atom(glm::vec3(2.5,0,0), 'O', am::bio::vdwRadii.find('O')->second, 'C'),
		am::bio::Atom(glm::vec3(-4,0,0), 'S', am::bio::vdwRadii.find('S')->second, 'C'),


	};

}
