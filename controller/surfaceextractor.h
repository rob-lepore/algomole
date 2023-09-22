#pragma once

#include "../am.h"
#include "../parsing/fileparser.h"
#include "../spacefilling/spacefiller.h"
#include "../meshing/mesher.h"
#include "../preprocessing/preprocessing.h"
#include "../postprocessing/postprocessing.h"

 /**
  * @brief The SurfaceExtractor class is responsible for computing a surface mesh
  *        using the specified components.
  *
  * This class coordinates the meshing pipeline steps involving FileParser, Preprocessing,
  * SpaceFiller, Mesher, and Postprocessing to generate a surface mesh.
  */

class am::pipeline::controller::SurfaceExtractor
{

public:
	/**
	 * @brief Constructor for the SurfaceExtractor class.
	 *
	 * @param fp A pointer to the FileParser instance.
	 * @param pre A pointer to the Preprocessing instance.
	 * @param sf A pointer to the SpaceFiller instance.
	 * @param m A pointer to the Mesher instance.
	 * @param post A pointer to the Postprocessing instance.
	 * @param opts A map containing additional options as key-value pairs.
	 */
	am::pipeline::controller::SurfaceExtractor(FileParser* fp, Preprocessing* pre, SpaceFiller* sf, Mesher* m, Postprocessing* post, std::unordered_map<std::string, float> opts);
	
	/**
	 * @brief Generates a surface mesh from the specified file.
	 *
	 * This method processes the input file to generate a surface mesh using the
	 * configured pipeline components.
	 *
	 * @param file String of the file content.
	 * @return A pointer to the generated surface mesh.
	 */
	am::gfx::Mesh* generateSurfaceMesh(std::string file);

private:
	am::pipeline::FileParser* m_fileParser; 
	am::pipeline::SpaceFiller* m_spacefiller;
	am::pipeline::Mesher* m_mesher;
	am::pipeline::Preprocessing* m_pre;
	am::pipeline::Postprocessing* m_post;
	std::unordered_map<std::string, float> m_opts;
	
};

