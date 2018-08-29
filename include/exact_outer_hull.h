#ifndef IMATISTL_EXACT_OUTER_HULL_H
#define IMATISTL_EXACT_OUTER_HULL_H

#include <Eigen/Core>
#include <imatistl.h>
#include "mesh_to_trimesh.h"
#include "trimesh_to_mesh.h"

namespace imatistl {

    #define OH_ITERATIONS 4
    #define OH_EPSILON_AREA 1.0e-6
    #define OH_DEFAULT_THICKNESS 1000.0

    void exact_outer_hull(IMATI_STL::TriMesh & T, double t=-1.0) {
        if (t < 0) t = T.bboxLongestDiagonal() / OH_DEFAULT_THICKNESS;
        IMATI_STL::coord _t(t);
        const double ea = T.area() * OH_EPSILON_AREA;

        for (int n = -1, it = 0; n != 0 && it < OH_ITERATIONS; ++it) {
            T.safeCoordBackApproximation();	
            auto D = T.computeOuterHull(false, 0);
            n = D->removeSmallestComponents(ea);
            n = T.removeSmallestComponents(ea);
            n = D->T.numels();

            T.removeRedundantVertices(); 
            T.delaunizeFlatAreas();
            D->removeRedundantVertices();
            D->delaunizeFlatAreas();

            if (n != 0 && it < OH_ITERATIONS - 1) { 
                D->toThinShell(_t); 
                T.moveMeshElements(D); 
            }
        } 
        T.deselectTriangles();
    }

    template <
        typename DerivedV,
        typename DerivedF>
    void exact_outer_hull(
        const Eigen::PlainObjectBase<DerivedV> & V,
        const Eigen::PlainObjectBase<DerivedF> & F,
        Eigen::PlainObjectBase<DerivedV> & VV,
        Eigen::PlainObjectBase<DerivedF> & FF,
        double t=-1.0
    ) {
        IMATI_STL::TriMesh T;
        mesh_to_trimesh(V, F, T);
        exact_outer_hull(T, t);
        trimesh_to_mesh(T, VV, FF);
    }
}

#endif