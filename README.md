# AlgoMole:  A Molecular Surface Meshing Library



AlgoMole is a C++ static library designed for the development and analysis of algorithms for molecular surface meshing. Molecular surfaces are crucial in various scientific domains, including computational biology, chemistry, and drug discovery. AlgoMole empowers researchers and developers to create, fine-tune, and evaluate algorithms for generating accurate molecular surfaces.

AlgoMole adopts a modular pipeline architecture. This architecture can be described as a sequential series of components, each responsible for a specific task. Data flows from one component to the next, with each component taking input from the previous one and passing output to the subsequent one.

Here's an overview of the components in AlgoMole's pipeline architecture:

 1. **File Parsing**: The first step is extracting molecular data from a file. AlgoMole supports input from PDB format file.
 2.  **Pre-processing:** This phase focuses on preparing and adjusting the molecular data for further processing.
    
 3.  **Space Filling:** In this step, the molecular space is discretized into a 3D grid, and the algorithm identifies which grid points are within the molecular volume.
    
 4.  **Meshing:** The meshing component produces a polygonal surface that effectively separates the molecular volume from the surrounding space.
    
 5.  **Post-processing:** While not altering the fundamental shape of the molecule, the post-processing phase refines the meshed surface. It is responsible for enhancing the surface's quality, including memory usage optimization and reducing errors related to surface area and volume calculations.
    
 6.  **Validation:** A validation system is integrated to assess the quality of the generated molecular surfaces. It compares measurements of surface area and volume with calculations by UCSF Chimera to validate the results.

## Installation

### Prerequisites

Before you can use AlgoMole, ensure you have the following prerequisites installed on your system:

-   C++ Compiler
-   [GLM](https://github.com/g-truc/glm) Library
-   [CGAL](https://www.cgal.org/) Library (optional)
-   [Boost](https://www.boost.org/doc/libs/1_83_0/index.html) Library (optional, only for validation)
-   [UCSF Chimera](https://www.cgl.ucsf.edu/chimera/) (optional, only for validation)

### Installation steps

1.  **Extract the AlgoMole Package:**
    
    Download the latest release and extract its contents to a directory of your choice.
    
2.  **Include Header Files:**
    
    In your C++ project, include the necessary AlgoMole header files. Ensure that the `include` directory from the extracted package is in your project's include path.
    
3.  **Link with the AlgoMole Library:**
    
    Link your project with the AlgoMole static library (`.lib` file) from the package. You may need to specify the library path.

## Examples

### 1. Export a molecular surface as OBJ file

    
    #include <algomole/controller/surfaceextractorbuilder.h>
    #include <algomole/parsing/pdbfileparser.h>
    #include <algomole/preprocessing/boundingboxpreprocessing.h>
    #include <algomole/spacefilling/edtspacefiller.h>
    #include <algomole/meshing/marchingcubesmesher.h>
    #include <algomole/postprocessing/laplacianpostprocessing.h>
    
    int main() {
        /* read PDB file */
        std::ifstream file("molecule.pdb");
        std::string content((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
        file.close();


        using namespace am::pipeline;
        controller::SurfaceExtractorBuilder builder;
        controller::SurfaceExtractor se = builder
            .setFileParser(new PdbFileParser)
            .setPreprocessing(new BoundingBoxPreprocessing)
            .setSpaceFiller(new EDTSpaceFiller)
            .setMeshBuilder(new MarchingCubesMesher)
            .setPostprocessing(new LaplacianPostprocessing)
            .setOption("size", 256)
            .setOption("surface", options::MS)
            .setOption("normals", options::SMOOTH)
            .build();
        
        am::gfx::Mesh* m = se.generateSurfaceMesh(content);
        m->toObjFile("molecule.obj");
    }

### 2. Director and validation

    #include <algomole/controller/director.h>
    #include <algomole/utils/validator.h>
    #include <iostream>
        
    int main() {
	   /* read PDB file */
	   std::ifstream file("molecule.pdb");
	   std::string content((std::istreambuf_iterator<char>(file)),
	       std::istreambuf_iterator<char>());
	   file.close();
    
       am::utils::Validator validator("C:/Program Files/Chimera 1.17.3/bin");
    
       using namespace am::pipeline::controller;
       SurfaceExtractorBuilder builder;
       Director director;
       director.make(builder, Director::Type::GAUSSIAN);
       SurfaceExtractor se = builder.build();
       am::gfx::Mesh* m = se.generateSurfaceMesh(content);
       std::cout << "Area relative error: " << validator.areaRelativeError(content, m) * 100. << "%\n"; 
    }

