#include "alphawrapmesher.h"
#include "../utils/cgalutils.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/alpha_wrap_3.h>
#include <CGAL/IO/read_points.h>
#include <CGAL/Real_timer.h>
#include <iostream>
#include <string>
using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point_3 = K::Point_3;
using Point_container = std::vector<Point_3>;
using Mesh = CGAL::Surface_mesh<Point_3>;

am::gfx::Mesh* AlphaWrapMesher::buildMesh(am::math::Mat3D<am::pipeline::GridPoint>& volume, std::unordered_map<std::string, float>& opts) {
    Point_container points;

    int size = am::pipeline::options::getOptionWithError(opts, "size");
    const double relative_alpha = am::pipeline::options::getOption(opts, "relative_alpha", 100);
    const double relative_offset = am::pipeline::options::getOption(opts, "relative_offset", 500);
    float value = am::pipeline::options::getOption(opts, "isovalue", 1);


    int o = -size / 2;
    for (int i = 0; i < volume.width(); i++) {
        for (int j = 0; j < volume.width(); j++) {
            for (int k = 0; k < volume.width(); k++) {
                if (volume.at(i, j, k).value >= value) {
                    points.push_back(Point_3(o + i, o + j, o + k));
                }
            }
        }
    }

    
    CGAL::Bbox_3 bbox = CGAL::bbox_3(std::cbegin(points), std::cend(points));
    const double diag_length = std::sqrt(CGAL::square(bbox.xmax() - bbox.xmin()) +
        CGAL::square(bbox.ymax() - bbox.ymin()) +
        CGAL::square(bbox.zmax() - bbox.zmin()));
    const double alpha = diag_length / relative_alpha;
    const double offset = diag_length / relative_offset;

    // Construct the wrap
    Mesh wrap;
    CGAL::alpha_wrap_3(points, alpha, offset, wrap);

    return am::utils::CgalUtils::convertFromCGALMesh(wrap);
    
}