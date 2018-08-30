#ifndef IMATISTL_MESH_TO_TRIMESH_H
#define IMATISTL_MESH_TO_TRIMESH_H

#include <Eigen/Core>
#include <imatistl.h>
#include <vector>
#include <memory>

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
        std::vector<IMATI_STL::ExtVertex *> EV(V.rows()); 
        std::vector<std::shared_ptr<IMATI_STL::ExtVertex>> EVp(V.rows()); // To avoid malloc/new
        for(int ii = 0; ii < V.rows(); ii++) {
            auto v = T.newVertex(V(ii, 0), V(ii, 1), V(ii, 2));
            T.V.appendTail(v);
            EVp[ii]  = std::make_shared<IMATI_STL::ExtVertex>(v);
            EV[ii]  = EVp[ii].get();
        }
        for(int ii = 0; ii < F.rows(); ii++) {
            T.CreateIndexedTriangle(EV.data(), F(ii, 0), F(ii, 1), F(ii, 2));
        }
        T.rebuildConnectivity();
    }
}

#endif