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
    namespace bio {

        const std::map<char, float> vdwRadii{
            {'C', 1.7},
            {'N', 1.5},
            {'O', 1.5},
            {'S', 1.8},
            {'X', 2.1},
            {'Y', 1.8}
        };

        const std::map<char, glm::vec4> colors{
            {'C', {0.15,0.4,0.3,1}},
            {'N', {0,0,1,1}},
            {'O', {1,0,0,1}},
            {'S', {1,1,0,1}},
        };

        const std::map<char, glm::vec4> chainColors{
            {'A', {0,1,0,1}},  //green
            {'B', {0,0,1,1}},  //blue
            {'C', {1,0,0,1}},  //red
            {'D', {1,1,0,1}},  //yellow
            {'E', {1,0,1,1}},  //magenta
            {'F', {0,1,1,1}},  //cyan

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
}

namespace am{
    namespace gfx {
        class Mesh;
        class ObjMeshVector;

        typedef struct Vertex {
            glm::vec4 position;
            glm::vec4 color;
            glm::vec3 normal;

            Vertex(glm::vec4 pos, glm::vec4 col) {
                position = pos;
                color = col;
                normal = glm::vec3(0);
            }
        } Vertex;

        typedef struct {
            unsigned int light_color_pointer;
            unsigned int light_power_pointer;
            unsigned int light_vector_pointer;
            unsigned int material_diffuse;
            unsigned int material_ambient;
            unsigned int material_specular;
            unsigned int material_shininess;
        } LightShaderUniform;

        typedef struct {
            glm::vec4 vector;
            glm::vec3 color;
            float power;
        } Light;

        typedef struct {
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            float shininess;
        } Material;

        /*
        GLuint loadShader(const char* filename, GLenum shader_type);
        Mesh* loadMeshFromFile(const char* filename);
        bool loadAssImp(const char* path, std::vector<am::gfx::Mesh*>& mymesh);
        */
    }
}
