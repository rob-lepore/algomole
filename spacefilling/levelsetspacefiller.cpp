#include "levelsetspacefiller.h"
using namespace am::pipeline;
am::math::Mat3D<GridPoint> LevelSetSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts)
{
	return am::math::Mat3D<GridPoint>(1,1,1);
}
