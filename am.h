#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <map>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

//typedef unsigned int GLenum;
typedef unsigned char byte;

namespace am{

    enum SurfaceType { VDWS = 1, SAS = 2, MS = 3 };
    enum ColorMode { ELEMENT, CHAIN, MONO };
    enum Bool { AM_FALSE, AM_TRUE };
    enum RenderMode { TRIANGLES = 4, POINTS = 0};
    enum Effect {SMOOTH, SHARP};

    namespace bio {

        const std::map<char, float> vdwRadii{
            {'C', 1.7},
            {'N', 1.5},
            {'O', 1.5},
            {'S', 1.8},
            {'P', 1.8},
            {'X', 2.1},
            {'Y', 1.8}
        };

        const std::map<char, glm::vec4> colors{
            {'C', {0.15,0.4,0.3,1}},
            {'N', {0,0,1,1}},
            {'O', {1,0,0,1}},
            {'S', {1,1,0,1}},
            {'P', {1,0.5,0,1}},
            {'X', {0,1,0.5,1}},

        };

        const std::map<char, glm::vec4> chainColors{
            {'A', {0, 1, 0, 1}},    // green
            {'B', {0, 0, 1, 1}},    // blue
            {'C', {1, 0, 0, 1}},    // red
            {'D', {1, 1, 0, 1}},    // yellow
            {'E', {1, 0, 1, 1}},    // magenta
            {'F', {0, 1, 1, 1}},    // cyan
            {'G', {1, 0.5, 0, 1}},  // orange
            {'H', {1, 0, 0.5, 1}},  // pink
            {'I', {0.5, 1, 0, 1}},  // lime green
            {'J', {0, 1, 0.5, 1}},  // teal
            {'K', {1, 0.5, 0.5, 1}}, // light pink
            {'L', {0.5, 1, 0.5, 1}}, // light green
            {'M', {0.5, 0.5, 1, 1}}, // light blue
            {'N', {0.8, 0, 0, 1}},  // bright red
            {'O', {0, 0.8, 0, 1}},  // bright green
            {'P', {0, 0, 0.8, 1}},  // bright blue
            {'Q', {0.8, 0, 0.8, 1}}, // bright magenta
            {'R', {0, 0.8, 0.8, 1}}, // bright cyan
            {'S', {0.8, 0.8, 0, 1}}, // bright yellow
            {'T', {1, 0.4, 0, 1}},  // vivid orange
            {'U', {1, 0, 0.4, 1}},  // vivid pink
            {'V', {0.4, 1, 0, 1}},  // vivid green
            {'W', {0, 0.4, 1, 1}},  // vivid blue
            {'X', {0.4, 0, 1, 1}},  // vivid purple
            {'Y', {1, 0, 0.4, 1}},  // vivid red
            {'Z', {0.4, 0, 1, 1}}   // vivid purple
        };



        typedef struct Atom {
            glm::vec3 position;
            char element;
            float radius;
            char chainId;
            Atom(glm::vec3 pos, char el, float r) {
                position = pos;
                element = el;
                radius = r;
                chainId = 0;
            }
            Atom(glm::vec3 pos, char el, float r, char chain) {
                position = pos;
                element = el;
                radius = r;
                chainId = chain;
            }
            Atom() {
                Atom(glm::vec3(0), ' ', 0);
            }
        } Atom;

    }

    typedef struct GridPoint {
        am::bio::Atom atom;
        float value;
    } GridPoint;
}

namespace am{
    namespace gfx {
        class Mesh;
        class ObjMeshVector;

        typedef struct Vertex {
            glm::vec4 position;
            glm::vec4 color;
            glm::vec4 normal;

            Vertex(glm::vec4 pos, glm::vec4 col) {
                position = pos;
                color = col;
                normal = glm::vec4(0);
            }

            Vertex() {
                position = glm::vec4(NAN);
                color = glm::vec4(0);
                normal = glm::vec4(0);
            }
        } Vertex;

        
    }
}
