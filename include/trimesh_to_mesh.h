#ifndef IMATISTL_TRIMESH_TO_MESH_H
#define IMATISTL_TRIMESH_TO_MESH_H

#include <Eigen/Core>
#include <imatistl.h>


template <
    typename DerivedV,
    typename DerivedF>
void trimesh_to_mesh(
    IMATI_STL::TriMesh & T,
    Eigen::PlainObjectBase<DerivedV> & V,
    Eigen::PlainObjectBase<DerivedF> & F
) {
    V.resize(T.V.numels(), 3);
    F.resize(T.T.numels(), 3);
    IMATI_STL::Node *n;
    IMATI_STL::Vertex *v;
    int ii = 0;
    for (n = T.V.head(), v = (n)?((IMATI_STL::Vertex *)n->data):NULL; n != NULL; n=n->next(), v = (n)?((IMATI_STL::Vertex *)n->data):NULL) {
        V(ii, 0) = v->x.toDouble();
        V(ii, 1) = v->y.toDouble();
        V(ii, 2) = v->z.toDouble();
        v->x = ii++; //Taken from TMesh/io.cpp
    }

    IMATI_STL::Triangle *t;
    ii = 0;
    for (n = T.T.head(), t = (n)?((IMATI_STL::Triangle *)n->data):NULL; n != NULL; n=n->next(), t = (n)?((IMATI_STL::Triangle *)n->data):NULL) {
        F(ii, 0) = t->v1()->x.toInt();
        F(ii, 1) = t->v2()->x.toInt();
        F(ii++, 2) = t->v3()->x.toInt();
    }

    for (n = T.V.head(), v = (n)?((IMATI_STL::Vertex *)n->data):NULL; n != NULL; n=n->next(), v = (n)?((IMATI_STL::Vertex *)n->data):NULL) {
        v->x = V(v->x.toInt(), 0);
    }
}

#endif