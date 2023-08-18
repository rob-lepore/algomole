#include "atomspacefiller.h"
#include <iostream>

inline float dist2(glm::vec3 a, glm::vec3 b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return ((dx * dx) + (dy * dy) + (dz * dz));
}

inline std::vector<glm::vec3> getPoints(glm::vec3 center, float r) {
    glm::vec3 min = center - glm::vec3(r);
    glm::vec3 max = center + glm::vec3(r);
    std::vector<glm::vec3> points;

    for (int x = min.x; x <= max.x; x++) {
        for (int y = min.y; y <= max.y; y++) {
            for (int z = min.z; z <= max.z; z++) {
                if (dist2(glm::vec3(x, y, z), center) <= r * r) {
                    points.push_back(glm::vec3(x, y, z));
                }
            }
        }
    }
    return points;
}


am::Mat3D<am::GridPoint> AtomSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) {
    float isize = opts["size"];
    float resolution = opts["resolution"];

    int size = std::floor(isize * resolution);
    am::Mat3D<am::GridPoint> volume(size, size, size, { am::bio::Atom(glm::vec3(0), ' ', 0), 0 });

    glm::vec3 origin = glm::vec3(-size / 2);

    for (const auto& atom : atoms) {

        int x_centro = size / 2 + atom.position.x * resolution;
        int y_centro = size / 2 + atom.position.y * resolution;
        int z_centro = size / 2 + atom.position.z * resolution;
        float raggio = atom.radius * resolution;
        glm::vec3 centro = glm::vec3(x_centro, y_centro, z_centro);

        std::vector<glm::vec3> punti_sfera = getPoints(centro, raggio);
        //std::cout << x_centro << " " << y_centro << " " << z_centro << " " << raggio << "\n";
        for (const auto& punto : punti_sfera) {
            //std::cout << "Punto: (" << punto.x << ", " << punto.y << ", " << punto.z << ")" << std::endl;
            volume.at(punto.x, punto.y, punto.z).atom = am::bio::Atom(atom.position, atom.element, atom.radius, atom.chainId);
            volume.at(punto.x, punto.y, punto.z).value = 1;
        }
    }
    return volume;
}


