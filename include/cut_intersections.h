
#ifndef IMATISTL_CUT_INTERSECTIONS_H
#define IMATISTL_CUT_INTERSECTIONS_H

#include <Eigen/Core>
#include <imatistl.h>
#include "mesh_to_trimesh.h"
#include "trimesh_to_mesh.h"

namespace imatistl {

    void cut_intersections(IMATI_STL::TriMesh & T) {
        T.cutIntersections();
    }

    template <
        typename DerivedV,
        typename DerivedF>
    void cut_intersections(
        const Eigen::PlainObjectBase<DerivedV> & V,
        const Eigen::PlainObjectBase<DerivedF> & F,
        Eigen::PlainObjectBase<DerivedV> & VV,
        Eigen::PlainObjectBase<DerivedF> & FF
    ) {
        IMATI_STL::TriMesh T;
        mesh_to_trimesh(V, F, T);
        cut_intersections(T);
        trimesh_to_mesh(T, VV, FF);
    }
}

#endif