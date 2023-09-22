/**
 * @file am.h
 *
 * @brief Definition of namespaces, constants and structs.
 */

#pragma once
#include <map>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

namespace am{

    namespace bio { 

        /**
         * @brief Map of van der Waals radii for common chemical elements.
         *
         * This map associates chemical element symbols (characters) with their respective van der Waals radii (in Ångströms).
         */
        const std::map<char, float> vdwRadii{
            {'C', 1.88},
            {'N', 1.64},
            {'O', 1.42},
            {'S', 1.77},
            {'P', 1.87},
            {'X', 2.1},
            {'Y', 1.8}
        };

        /**
         * @brief The Atom struct represents useful atomic data.
         */
        typedef struct Atom {
            glm::vec3 position;
            char element;
            float radius;
            char chainId;

            /**
             * @brief Constructs an Atom object with default values.
             */
            Atom() : position(glm::vec3(0)), element(' '), radius(0), chainId(0) {}

            /**
             * @brief Constructs an Atom object with specified values.
             *
             * @param pos The 3D position of the atom.
             * @param el The chemical element symbol of the atom.
             * @param r The van der Waals radius of the atom (in Ångströms).
             * @param chain The chain identifier of the atom (optional).
             */
            Atom(glm::vec3 pos, char el, float r, char chain = 0) : position(pos), element(el), radius(r), chainId(chain) {}

        } Atom;

    }

    namespace gfx { 
        class Mesh;

        /**
         * @brief Constructs a Vertex object with specified position and color.
         *
         * The normal vector is initialized to (0,0,0,0).
         *
         * @param pos The position of the vertex in homogeneous coordinates.
         * @param col The color of the vertex.
         */
        typedef struct Vertex {
            glm::vec4 position;
            glm::vec4 color;
            glm::vec4 normal;
            /**
             * @brief Constructs a Vertex object with specified position and color.
             *
             * The normal vector is initialized to (0,0,0,0).
             *
             * @param pos The position of the vertex in homogeneous coordinates.
             * @param col The color of the vertex.
             * @param norm The normal vector in the vertex in homogeneous coordinates.
             * 
             */
            Vertex(glm::vec4 pos, glm::vec4 col, glm::vec4 norm = glm::vec4(0)) : position(pos), color(col), normal(norm) {}

            /**
             * @brief Constructs a Vertex object with default values.
             *
             * The position is initialized with NaN values, color is (0,0,0,0), and normal is (0,0,0,0).
             */
            Vertex() {
                position = glm::vec4(NAN);
                color = glm::vec4(0);
                normal = glm::vec4(0);
            }
        } Vertex;

        /**
         * @brief Map of element colors for common chemical elements.
         *
         * This map associates chemical element symbols with their respective RGBA color vectors.
         */
        const std::map<char, glm::vec4> elementColors{
            {'C', {0.15,0.4,0.3,1}},
            {'N', {0,0,1,1}},
            {'O', {1,0,0,1}},
            {'S', {1,1,0,1}},
            {'P', {1,0.5,0,1}},
            {'X', {0,1,0.5,1}},
        };

        /**
         * @brief Map of element colors for chains from A to Z.
         *
         * This map associates chain IDs with their respective RGBA color vectors.
         */
        const std::map<char, glm::vec4> chainColors{
            {'A', {0, 1, 0, 1}},    
            {'B', {0, 0, 1, 1}},    
            {'C', {1, 0, 0, 1}},    
            {'D', {1, 1, 0, 1}},    
            {'E', {1, 0, 1, 1}},    
            {'F', {0, 1, 1, 1}},    
            {'G', {1, 0.5, 0, 1}},  
            {'H', {1, 0, 0.5, 1}},  
            {'I', {0.5, 1, 0, 1}},  
            {'J', {0, 1, 0.5, 1}},  
            {'K', {1, 0.5, 0.5, 1}},
            {'L', {0.5, 1, 0.5, 1}},
            {'M', {0.5, 0.5, 1, 1}},
            {'N', {0.8, 0, 0, 1}},  
            {'O', {0, 0.8, 0, 1}},  
            {'P', {0, 0, 0.8, 1}},  
            {'Q', {0.8, 0, 0.8, 1}},
            {'R', {0, 0.8, 0.8, 1}},
            {'S', {0.8, 0.8, 0, 1}},
            {'T', {1, 0.4, 0, 1}},  
            {'U', {1, 0, 0.4, 1}},  
            {'V', {0.4, 1, 0, 1}},  
            {'W', {0, 0.4, 1, 1}},  
            {'X', {0.4, 0, 1, 1}},  
            {'Y', {1, 0, 0.4, 1}},  
            {'Z', {0.4, 0, 1, 1}}    
        };
        
    }

    namespace pipeline { 
        namespace controller {
            class SurfaceExtractor;
            class SurfaceExtractorBuilder;
            class Director;
        }
        namespace options {
            /**
             * @brief Enumeration of surface types for mesh generation.
             */
            enum SurfaceType {
                VDWS = 1, /**< Van der Waals Surface. */
                SAS = 2, /**< Solvent Accessible Surface. */
                MS = 3 /**< Molecular Surface (Solvent Excluded Surface). */
            };

            /**
             * @brief Enumeration of color modes for mesh rendering.
             */
            enum ColorMode {
                ELEMENT, /**< Color by chemical element. */
                CHAIN, /**< Color by chain identifier. */
                MONO /**< Use the same color for the whole molecule. */
            };

            /**
             * @brief Enumeration of boolean values.
             */
            enum Bool {
                AM_FALSE, /**< False value. */
                AM_TRUE /**< True value. */
            };

            /**
             * @brief Enumeration of rendering modes for mesh visualization.
             */
            enum RenderMode {
                TRIANGLES = 4, /**< Triangle rendering mode. */
                POINTS = 0 /**< Point rendering mode. */
            };

            /**
             * @brief Enumeration of normal calculation modes.
             */
            enum Normals {
                SMOOTH, /**< Smooth normals. */
                SHARP /**< Sharp normals. */
            };

            /**
             * @brief Enumeration of logging mode.
             */
            enum Logging {
                NO, /**< No logging. */
                MINIMAL, /**< Minimal logging. */
                VERBOSE /**< Verbose logging. */
            };


            /**
             * @brief Retrieves an option value from an options map or returns a default value if the option is not found.
             *
             * This function searches the options map for a specified key. If the key is found, it returns the associated value.
             * Otherwise, it returns the provided default value.
             *
             * @param options The options map.
             * @param key The key to look up in the options map.
             * @param defaultValue The default value to return if the key is not found.
             * @return The option value if found, or the default value if not found.
             */
            float getOption(std::unordered_map<std::string, float>& options, std::string key, float defaultValue);

            /**
             * @brief Retrieves an option value from an options map or throws an error if the option is not found.
             *
             * This function searches the options map for a specified key. If the key is found, it returns the associated value.
             * If the key is not found, it throws an error indicating the missing option.
             *
             * @param options The options map.
             * @param key The key to look up in the options map.
             * @return The option value if found.
             * @throws MissingOptionException if the key is not found in the options map.
             */
            float getOptionWithError(std::unordered_map<std::string, float>& options, std::string key);
            
            /**
             * @brief Asserts that an option has a specific value in an options map.
             *
             * This function checks if the specified key in the options map has the expected value. If the key exists but has a
             * different value, it throws an error indicating the mismatched option value.
             *
             * @param options The options map.
             * @param key The key to check in the options map.
             * @param value The expected value for the option.
             * @throws InvalidOptionException if the key's value does not match the expected value.
             * @throws MissingOptionException if the key is not found in the options map.
             */
            void assertOptionValue(std::unordered_map<std::string, float>& options, std::string key, float value);

            class OptionException;
            class MissingOptionException;
            class InvalidOptionException;

        }

        /**
         * @brief The GridPoint struct represents a point in a discretized space.
         */
        typedef struct GridPoint {
            am::bio::Atom atom; /**< The atom relative to the grid point. */
            float value; /**< The value associated with the grid point. */

            /**
             * @brief Constructs a GridPoint object with specified atom and value.
             *
             * @param a The Atom object associated with the grid point.
             * @param v The value associated with the grid point.
             */
            GridPoint(am::bio::Atom a, float v) : atom(a), value(v) {}
        } GridPoint;

        class FileParser;
        class PdbFileParser;

        class Preprocessing;
        class BoundingBoxPreprocessing;

        class SpaceFiller;
        class GridSpaceFiller;
        class AtomSpaceFiller;
        class EDTSpaceFiller;
        class GaussianSpaceFiller;
        class LevelSetSpaceFiller;

        class Mesher;
        class MarchingCubesMesher;

        class Postprocessing;
        class LaplacianPostprocessing;
        class NonePostprocessing;
    }

    namespace utils {
        class Logger;
        class CgalUtils;
        class Validator;
    }

}
