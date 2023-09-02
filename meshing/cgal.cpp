#include "cgal.h"
#include "../utils/cgalutils.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Skin_surface_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_skin_surface_3.h>
#include <CGAL/subdivide_skin_surface_mesh_3.h>
#include <list>
#include <fstream>
#include <CGAL/Surface_mesh.h>
#include <CGAL/make_skin_surface_mesh_3.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Skin_surface_traits_3<K>                      Traits;
typedef CGAL::Skin_surface_3<Traits>                        Skin_surface_3;
typedef Skin_surface_3::FT                                  FT;
typedef Skin_surface_3::Bare_point                          Bare_point;
typedef Skin_surface_3::Weighted_point                      Weighted_point;
typedef CGAL::Polyhedron_3<K,
    CGAL::Skin_surface_polyhedral_items_3<Skin_surface_3> >   Polyhedron;
using Point_3 = K::Point_3;
using Mesh = CGAL::Surface_mesh<Point_3>;


am::gfx::Mesh* Cgal::buildMesh(am::math::Mat3D<am::pipeline::GridPoint>& volume, std::unordered_map<std::string, float>& opts) {
    std::list<Weighted_point> l;
    FT                        s = 0.5;

    for (int i = 0; i < volume.width(); i++) {
        glm::vec3 pos = volume.at(i, 0, 0).atom.position;
        float r = volume.at(i, 0, 0).atom.radius;
        l.push_front(Weighted_point(Bare_point(pos.x, pos.y, pos.z),r*r*(1/s)));
    }
    Mesh m;

    Polyhedron p;
    Skin_surface_3 skin_surface(l.begin(), l.end(), s);
    CGAL::mesh_skin_surface_3(skin_surface, p);
    //CGAL::subdivide_skin_surface_mesh_3(skin_surface, p);

    
    std::ofstream out("mesh.off");
    out << p;
    out.close();
    std::ifstream in("mesh.off");
    CGAL::IO::read_OFF(in, m);
    in.close();
    
    return am::utils::CgalUtils::convertFromCGALMesh(m);;
}