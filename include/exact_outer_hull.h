#ifndef IMATISTL_EXACT_OUTER_HULL_H
#define IMATISTL_EXACT_OUTER_HULL_H

#include <Eigen/Core>
#include <imatistl.h>
#include "mesh_to_trimesh.h"
#include "trimesh_to_mesh.h"

namespace imatistl {

    void exact_outer_hull(IMATI_STL::TriMesh & T, double t=-1.0, double ea=1.0e-6, int it=4) {
        if (t < 0) t = T.bboxLongestDiagonal() / 1000.0;
        IMATI_STL::coord _t(t);
        ea = T.area() * ea;

        for (int n = -1; n != 0 && it > 0; --it) {
            T.safeCoordBackApproximation();	
            auto D = T.computeOuterHull();
            n = D->removeSmallestComponents(ea);
            n = T.removeSmallestComponents(ea);
            n = D->T.numels();

            T.removeRedundantVertices(); 
            T.delaunizeFlatAreas();
            D->removeRedundantVertices();
            D->delaunizeFlatAreas();

            if (n != 0 && it != 0) { 
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
        double t=-1.0,
        double ea=1.0e-6,
        int it=4
    ) {
        IMATI_STL::TriMesh T;
        mesh_to_trimesh(V, F, T);
        exact_outer_hull(T, t, ea, it);
        trimesh_to_mesh(T, VV, FF);
    }
}

#endif