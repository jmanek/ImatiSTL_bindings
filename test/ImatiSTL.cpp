#include <Eigen/Core>
#include <imatistl.h>
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include "exact_outer_hull.h"
#include <iostream>
int main() { 
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::readOBJ("../test/box.obj", V, F);
    IMATI_STL::TriMesh T;
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    std::cout<< V.rows() <<std::endl;
    std::cout<< F.rows() <<std::endl;
    exact_outer_hull(V,F,VV,FF, 0.0001);
    // igl::writeOBJ("../test/box_out.obj", VV, FF);

    return 0;
    
}