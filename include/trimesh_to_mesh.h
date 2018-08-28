#ifndef IMATISTL_TRIMESH_TO_MESH_H
#define IMATISTL_TRIMESH_TO_MESH_H

#include <Eigen/Core>
#include <imatistl.h>
#include <unordered_map>

namespace imatistl {
    template <
        typename DerivedV,
        typename DerivedF>
    void trimesh_to_mesh(
        const IMATI_STL::TriMesh & T,
        Eigen::PlainObjectBase<DerivedV> & V,
        Eigen::PlainObjectBase<DerivedF> & F
    ) {
        V.resize(T.V.numels(), 3);
        F.resize(T.T.numels(), 3);
        
        std::unordered_map<const IMATI_STL::Vertex *, int> vi;
        IMATI_STL::Node *n;
        int ii;
        for (n = T.V.head(), ii = 0; n != NULL; n = n->next(), ++ii) {
            auto v = (IMATI_STL::Vertex *) n->data;
            V(ii, 0) = v->x.toDouble();
            V(ii, 1) = v->y.toDouble();
            V(ii, 2) = v->z.toDouble();
            vi[v] = ii;
        }

        for (n = T.T.head(), ii = 0; n != NULL; n = n->next(), ++ii) {
            auto t = (IMATI_STL::Triangle *) n->data;
            F(ii, 0) = vi[t->v1()];
            F(ii, 1) = vi[t->v2()];
            F(ii, 2) = vi[t->v3()];
        }
    }
}

#endif