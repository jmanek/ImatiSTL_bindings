#ifndef IMATISTL_MESH_TO_TRIMESH_H
#define IMATISTL_MESH_TO_TRIMESH_H

#include <Eigen/Core>
#include <imatistl.h>

namespace imatistl {
    template <
        typename DerivedV,
        typename DerivedF>
    void mesh_to_trimesh(
        const Eigen::PlainObjectBase<DerivedV> & V,
        const Eigen::PlainObjectBase<DerivedF> & F,
        IMATI_STL::TriMesh & T
    ) {
        T = IMATI_STL::TriMesh();
        auto **EV = (IMATI_STL::ExtVertex **)malloc(sizeof(IMATI_STL::ExtVertex *) * V.rows());
        for(int ii = 0; ii < V.rows(); ii++) {
            auto *v = T.newVertex(V(ii, 0), V(ii, 1), V(ii, 2));
            T.V.appendTail(v);
            EV[ii]  = new IMATI_STL::ExtVertex(v);
        }
        for(int ii = 0; ii < F.rows(); ii++) {
            T.CreateIndexedTriangle(EV, F(ii, 0), F(ii, 1), F(ii, 2));
        }
        T.rebuildConnectivity();
    }
}

#endif