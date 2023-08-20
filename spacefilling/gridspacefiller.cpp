#include "gridspacefiller.h"
#include <iostream>
am::Mat3D<am::GridPoint> GridSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) {
    int size = opts["size"];
    am::Mat3D<am::GridPoint> volume(size, size, size);

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
                        volume.at(i, j, k) = { am::bio::Atom(atom.position, atom.element, atom.radius, atom.chainId), 1 };
                        break;
                    }
                }


            }
        }
    }
    
    return volume;

}

float GridSpaceFiller::dist2(glm::vec4 a, glm::vec4 b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return ((dx * dx) + (dy * dy) + (dz * dz));
}