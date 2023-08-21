#include "levelsetspacefiller.h"

am::Mat3D<am::GridPoint> LevelSetSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts)
{
	return am::Mat3D<am::GridPoint>(1,1,1);
}
