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
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    std::cout << "Vertices: " << V.rows() << std::endl;
    std::cout << "Faces: " << F.rows() << std::endl;
    imatistl::exact_outer_hull(V,F,VV,FF, 0.01);
    std::cout << "Vertices: " << VV.rows() << std::endl;
    std::cout << "Faces: " << FF.rows() << std::endl;
    igl::writeOBJ("spheres_outer_hull.obj", VV, FF);
    return 0;
}