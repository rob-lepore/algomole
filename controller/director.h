#pragma once
#include "./surfaceextractorbuilder.h"


/**
 * @brief The Director class is responsible for directing the construction of
 *        SurfaceExtractor objects using the Builder pattern.
 *
 * This class allows users to specify the type of SurfaceExtractor they want to
 * create (either GAUSSIAN or EDT) and set a SurfaceExtractorBuilder object to construct it.
 */
class am::pipeline::controller::Director {
public:
	/**
	 * @brief Enum representing the types of SurfaceExtractor that can be created.
	 */
	enum Type {
		GAUSSIAN,  /**< Gaussian SurfaceExtractor type. */
		EDT};      /**< Euclidean Distance Transform (EDT) SurfaceExtractor type. */

	Director() {};

	/**
	 * @brief Sets the SurfaceExtractorBuilder according to the specified type.
	 *
	 * This method takes a SurfaceExtractorBuilder reference and a Type enum as
	 * arguments to set the builder to build a SurfaceExtractor based on the specified type.
	 *
	 *
	 * @param builder The SurfaceExtractorBuilder to be set.
	 * @param t The Type of SurfaceExtractor to create (GAUSSIAN or EDT).
	 */
	void make(SurfaceExtractorBuilder& builder, Type t);
};