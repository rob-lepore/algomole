#include "gridspacefiller.h"
#include "../exceptions/optionexception.h"
#include <iostream>
am::math::Mat3D<am::pipeline::GridPoint> am::pipeline::GridSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) {
    int size;
    try {
        size = options::getOptionWithError(opts, "size");
    }
    catch (options::OptionException& e) {
        throw e;
    }
    am::math::Mat3D<am::pipeline::GridPoint> volume(size, size, size);

    glm::vec3 origin = glm::vec3(-size / 2);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                volume.at(i, j, k) = { am::bio::Atom(), 0 };

                glm::vec4 pos = glm::vec4(origin.x + i, origin.y + j, origin.z + k, 1);

                for (int m = 0; m < atoms.size(); m++) {
                    am::bio::Atom atom = atoms[m];
                    float d = dist2(pos, glm::vec4(atom.position, 1));

                    // check if it is inside an atom
                    float radius = atom.radius; 
                    if (d < radius * radius) {
                        //volume.at(i, j, k) = { am::bio::Atom(atom.position, atom.element, atom.radius, atom.chainId), 1 };
                        volume.at(i, j, k).atom = am::bio::Atom(atom.position, atom.element, atom.radius, atom.chainId);
                        volume.at(i, j, k).value = 1;
                        break;
                    }
                }


            }
        }
    }
    
    return volume;

}

float am::pipeline::GridSpaceFiller::dist2(glm::vec4 a, glm::vec4 b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return ((dx * dx) + (dy * dy) + (dz * dz));
}