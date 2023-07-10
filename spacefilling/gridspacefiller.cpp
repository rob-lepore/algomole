#include "gridspacefiller.h"

am::Mat3D<byte> GridSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float> opts) {
    float isize = opts["size"];
    float resolution = opts["resolution"];

    int size = std::floor( isize * resolution );
    am::Mat3D<byte> volume(size, size, size, 0);

    glm::vec3 origin = glm::vec3(-size / 2);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {

                glm::vec4 pos = glm::vec4(origin.x + i, origin.y + j, origin.z + k, 1);

                bool match = false;
                for (int m = 0; m < atoms.size(); m++) {
                    am::bio::Atom atom = atoms[m];
                    float d = dist2(pos, glm::vec4(atom.position * resolution, 1));

                    // check if it is inside an atom
                    float radius = atom.radius * resolution;
                    if (d < radius * radius) {
                        match = true;
                        break;
                    }
                }

                volume.at(i,j,k) = match ? 1 : 0;


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