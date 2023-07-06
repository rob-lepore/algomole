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


typedef std::vector<std::vector<std::vector<byte>>> mat3D;

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
            {'C', {1,1,1,1}},
            {'N', {0,0,1,1}},
            {'O', {1,0,0,1}},
            {'S', {1,1,0,1}},
            {'X', {1,1,0,1}},
            {'Y', {1,1,0,1}}
        };

        typedef struct Atom {
            glm::vec3 position;
            char element;
            float radius;
        } Atom;
    }
}

namespace am{
    namespace gfx {
        class Mesh;
        class Camera;
        class ObjMeshVector;

        typedef struct {
            glm::vec4 position;
            glm::vec4 color;
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
