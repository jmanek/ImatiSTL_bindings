
#ifndef IMATISTL_FILL_SMALL_BOUNDARIES_H
#define IMATISTL_FILL_SMALL_BOUNDARIES_H

#include <Eigen/Core>
#include <imatistl.h>
#include "mesh_to_trimesh.h"
#include "trimesh_to_mesh.h"

namespace imatistl {

    void fill_small_boundaries(IMATI_STL::TriMesh & T) {
        T.fillSmallBoundaries();
        T.deselectTriangles();
    }

    template <
        typename DerivedV,
        typename DerivedF>
    void fill_small_boundaries(
        const Eigen::PlainObjectBase<DerivedV> & V,
        const Eigen::PlainObjectBase<DerivedF> & F,
        Eigen::PlainObjectBase<DerivedV> & VV,
        Eigen::PlainObjectBase<DerivedF> & FF
    ) {
        IMATI_STL::TriMesh T;
        mesh_to_trimesh(V, F, T);
        fill_small_boundaries(T);
        trimesh_to_mesh(T, VV, FF);
    }
}

#endif