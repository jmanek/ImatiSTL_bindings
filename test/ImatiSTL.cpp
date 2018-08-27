#include <Eigen/Core>
#include <imatistl.h>
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include "exact_outer_hull.h"

int main() { 
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::readOBJ("diamond_packed.obj", V, F);
    IMATI_STL::TriMesh T;
    Eigen::MatrixXd VV;
    Eigen::MatrixXi FF;
    exact_outer_hull(V,F,VV,FF);
    igl::writeOBJ("diamond_packed_out_libigl.obj", VV, FF);

    return 0;
    
}