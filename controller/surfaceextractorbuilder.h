#pragma once
#include "surfaceextractor.h"

/**
 * @brief The SurfaceExtractorBuilder class is responsible for constructing
 *        a SurfaceExtractor with the given components and options.
 *
 * This class allows users to configure and build a SurfaceExtractor by setting
 * its constituent parts and custom options.
 */

class am::pipeline::controller::SurfaceExtractorBuilder
{
public:
	/**
	 * @brief Set the FileParser for the SurfaceExtractor.
	 *
	 * @param fp A pointer to the FileParser instance.
	 * @return A reference to the updated SurfaceExtractorBuilder.
	 */
	SurfaceExtractorBuilder& setFileParser(FileParser* fp);

	/**
	* @brief Set the Preprocessing component for the SurfaceExtractor.
	*
	* @param p A pointer to the Preprocessing instance.
	* @return A reference to the updated SurfaceExtractorBuilder.
	*/
	SurfaceExtractorBuilder& setPreprocessing(Preprocessing* p);

	/**
	 * @brief Set the SpaceFiller component for the SurfaceExtractor.
	 *
	 * @param sf A pointer to the SpaceFiller instance.
	 * @return A reference to the updated SurfaceExtractorBuilder.
	 */
	SurfaceExtractorBuilder& setSpaceFiller(SpaceFiller* sf);

	/**
	 * @brief Set the MeshBuilder (Mesher) for the SurfaceExtractor.
	 *
	 * @param mb A pointer to the Mesher instance.
	 * @return A reference to the updated SurfaceExtractorBuilder.
	 */
	SurfaceExtractorBuilder& setMeshBuilder(Mesher* mb);

	/**
	 * @brief Set the Postprocessing component for the SurfaceExtractor.
	 *
	 * @param p A pointer to the Postprocessing instance.
	 * @return A reference to the updated SurfaceExtractorBuilder.
	 */
	SurfaceExtractorBuilder& setPostprocessing(Postprocessing* p);

	/**
	 * @brief Set an option for the SurfaceExtractor.
	 *
	 * @param key The key for the option.
	 * @param value The value for the option.
	 * @return A reference to the updated SurfaceExtractorBuilder.
	 */
	SurfaceExtractorBuilder& setOption(std::string key, float value);

	/**
	 * @brief Build a SurfaceExtractor with the configured components and options.
	 *
	 * @return A SurfaceExtractor object based on the configured settings.
	 */
	SurfaceExtractor build();


private:
	am::pipeline::FileParser* m_parser;
	am::pipeline::Preprocessing* m_pre;
	am::pipeline::SpaceFiller* m_spacefiller;
	am::pipeline::Mesher* m_mesher;
	am::pipeline::Postprocessing* m_post;
	std::unordered_map<std::string, float> m_opts;
};

