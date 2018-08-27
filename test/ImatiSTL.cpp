#include <Eigen/Core>
#include <imatistl.h>
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include "exact_outer_hull.h"
#include <iostream>

int main() { 
    
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::readOBJ("../test/spheres.obj", V, F);
    IMATI_STL::TriMesh T;
    imatistl::mesh_to_trimesh(V, F, T);
    std::cout << "Vertices: " << V.rows() << std::endl;
    std::cout << "Faces: " << F.rows() << std::endl;
    T.printReport();
    
    imatistl::exact_outer_hull(T, 0.01);
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    imatistl::trimesh_to_mesh(T, VV, FF);
    std::cout << "Vertices: " << VV.rows() << std::endl;
    std::cout << "Faces: " << FF.rows() << std::endl;
    T.printReport();
    
    igl::writeOBJ("spheres_outer_hull.obj", VV, FF);
    return 0;
}