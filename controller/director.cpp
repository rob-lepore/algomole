#include "director.h"

#include "../parsing/pdbfileparser.h"
#include "../preprocessing/boundingboxpreprocessing.h"
#include "../meshing/marchingcubesmesher.h"
#include "../spacefilling/gaussianspacefiller.h"
#include "../postprocessing/laplacianpostprocessing.h"

void am::pipeline::controller::Director::make(SurfaceExtractorBuilder& builder, Type t)
{
	switch (t)
	{
	case am::pipeline::controller::Director::GAUSSIAN:
		builder.setFileParser(new PdbFileParser)
			.setPreprocessing(new BoundingBoxPreprocessing)
			.setSpaceFiller(new GaussianSpaceFiller)
			.setMeshBuilder(new MarchingCubesMesher)
			.setPostprocessing(new LaplacianPostprocessing)
			.setOption("size", 256)
			.setOption("surface", options::VDWS)
			.setOption("color_mode", options::MONO)
			.build();
		break;
	case am::pipeline::controller::Director::EDT:
		break;
	default:
		break;
	}
}
