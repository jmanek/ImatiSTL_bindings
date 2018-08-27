#ifndef IMATISTL_EXACT_OUTER_HULL_H
#define IMATISTL_EXACT_OUTER_HULL_H

#include <Eigen/Core>
#include <imatistl.h>
#include "mesh_to_trimesh.h"
#include "trimesh_to_mesh.h"

namespace imatistl {

    void exact_outer_hull(IMATI_STL::TriMesh & T, double t=-1.0) {
        if (t < 0) t = T.bboxLongestDiagonal() / 1000.0; 
        IMATI_STL::coord _t(t);
        int n = 0, it = 1;
        const double ea = T.area() * 1.0e-6;

        do {
            T.safeCoordBackApproximation();	
            auto *D = T.computeOuterHull(false, 0);
            n = D->removeSmallestComponents(ea);
            n = T.removeSmallestComponents(ea);
            n = D->T.numels();

            T.removeRedundantVertices(); 
            T.delaunizeFlatAreas();
            D->removeRedundantVertices();
            D->delaunizeFlatAreas();

            if (n != 0 && it < 4) { 
                D->toThinShell(_t); 
                T.moveMeshElements(D); 
            }
            T.deselectTriangles();
        } while (n != 0 && it < 4);
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