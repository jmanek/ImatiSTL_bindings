#include <Eigen/Core>
#include <imatistl.h>
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include "exact_outer_hull.h"
#include "cut_intersections.h"
#include "fill_small_boundaries.h"
#include "mesh_to_trimesh.h"
#include "trimesh_to_mesh.h"
#include <iostream>

int main() { 
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::readOBJ("../test/spheres.obj", V, F);
    std::cout << "Vertices: " << V.rows() << std::endl;
    std::cout << "Faces: " << F.rows() << std::endl;
    
    
    IMATI_STL::TriMesh T;
    imatistl::mesh_to_trimesh(V, F, T);
    T.printReport();
    imatistl::cut_intersections(T);
    T.printReport();
    imatistl::mesh_to_trimesh(V, F, T);
    imatistl::fill_small_boundaries(T);
    T.printReport();
    imatistl::mesh_to_trimesh(V, F, T);
    imatistl::exact_outer_hull(T, 0.01);
    T.printReport();

    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    imatistl::trimesh_to_mesh(T, VV, FF);
    std::cout << "Vertices: " << VV.rows() << std::endl;
    std::cout << "Faces: " << FF.rows() << std::endl;
    igl::writeOBJ("spheres_outer_hull.obj", VV, FF);

    igl::readOBJ("../test/demoman.obj", V, F);
    imatistl::mesh_to_trimesh(V, F, T);
    T.printReport();
    imatistl::fill_small_boundaries(T);
    imatistl::exact_outer_hull(T, 0.1);
    T.printReport();
    imatistl::trimesh_to_mesh(T, VV, FF);
    igl::writeOBJ("demoman_repaired.obj", VV, FF);
}