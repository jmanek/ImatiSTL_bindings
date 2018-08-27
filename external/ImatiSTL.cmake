# We want to test the hybrid kernel.
ADD_DEFINITIONS(-DUSE_HYBRID_KERNEL)

# Add CGAL support.
ADD_DEFINITIONS(-DUSE_CGAL_LAZYNT)
SET(CGAL_DONT_OVERRIDE_CMAKE_FLAGS TRUE CACHE BOOL
    "Disable CGAL from overwriting my cmake flags")
FIND_PACKAGE(CGAL)
INCLUDE(${CGAL_USE_FILE})

INCLUDE_DIRECTORIES(
    ${IMATISTL_SOUCE_DIR}/include/Kernel/
    ${IMATISTL_SOUCE_DIR}/include/TMesh/
    ${IMATISTL_SOUCE_DIR}/include/ImatiSTL/)

#INCLUDE_DIRECTORIES(${IMATISTL_SOUCE_DIR}/mpir64/)

SET(KERNEL_INC
    ${IMATISTL_SOUCE_DIR}/include/Kernel/
    ${IMATISTL_SOUCE_DIR}/include/Kernel/basics.h
    ${IMATISTL_SOUCE_DIR}/include/Kernel/coordinates.h
    ${IMATISTL_SOUCE_DIR}/include/Kernel/graph.h
    ${IMATISTL_SOUCE_DIR}/include/Kernel/heap.h
    ${IMATISTL_SOUCE_DIR}/include/Kernel/jqsort.h
    ${IMATISTL_SOUCE_DIR}/include/Kernel/list.h
    ${IMATISTL_SOUCE_DIR}/include/Kernel/matrix.h
    ${IMATISTL_SOUCE_DIR}/include/Kernel/point.h
    ${IMATISTL_SOUCE_DIR}/include/Kernel/tmesh_kernel.h)

SET(TMESH_INC
    ${IMATISTL_SOUCE_DIR}/include/TMesh/detectIntersections.h
    ${IMATISTL_SOUCE_DIR}/include/TMesh/edge.h
    ${IMATISTL_SOUCE_DIR}/include/TMesh/edgeHeap.h
    ${IMATISTL_SOUCE_DIR}/include/TMesh/faceClustering.h
    ${IMATISTL_SOUCE_DIR}/include/TMesh/simplification.h
    ${IMATISTL_SOUCE_DIR}/include/TMesh/tin.h
    ${IMATISTL_SOUCE_DIR}/include/TMesh/tmesh.h
    ${IMATISTL_SOUCE_DIR}/include/TMesh/triangle.h
    ${IMATISTL_SOUCE_DIR}/include/TMesh/vertex.h)

SET(IMATISTL_INC
    ${IMATISTL_SOUCE_DIR}/include/ImatiSTL/cutIntersections.h
    ${IMATISTL_SOUCE_DIR}/include/ImatiSTL/dijkstraGraph.h
    ${IMATISTL_SOUCE_DIR}/include/ImatiSTL/imatistl.h
    ${IMATISTL_SOUCE_DIR}/include/ImatiSTL/marchIntersections.h
    ${IMATISTL_SOUCE_DIR}/include/ImatiSTL/trimesh.h)

SET(ALGORITHM_SRC
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/checkAndRepair.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/delaunize.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/detectIntersections.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/faceClustering.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/featureRecover.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/holeFilling.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/simplification.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/smoothing.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/spherize.cpp
    ${IMATISTL_SOUCE_DIR}/src/Algorithms/subdivision.cpp
    )

SET(IMATISTL_SRC
    ${IMATISTL_SOUCE_DIR}/src/ImatiSTL/computeOuterHull.cpp
    ${IMATISTL_SOUCE_DIR}/src/ImatiSTL/cutIntersections.cpp
    ${IMATISTL_SOUCE_DIR}/src/ImatiSTL/dijkstraGraph.cpp
    ${IMATISTL_SOUCE_DIR}/src/ImatiSTL/epsilonSampling.cpp
    ${IMATISTL_SOUCE_DIR}/src/ImatiSTL/marchIntersections.cpp
    ${IMATISTL_SOUCE_DIR}/src/ImatiSTL/offset.cpp
    ${IMATISTL_SOUCE_DIR}/src/ImatiSTL/uniformRemesh.cpp
    )

SET(KERNEL_SRC
    ${IMATISTL_SOUCE_DIR}/src/Kernel/orientation.cpp
    ${IMATISTL_SOUCE_DIR}/src/Kernel/coordinates.cpp
    ${IMATISTL_SOUCE_DIR}/src/Kernel/graph.cpp
    ${IMATISTL_SOUCE_DIR}/src/Kernel/heap.cpp
    ${IMATISTL_SOUCE_DIR}/src/Kernel/jqsort.cpp
    ${IMATISTL_SOUCE_DIR}/src/Kernel/list.cpp
    ${IMATISTL_SOUCE_DIR}/src/Kernel/matrix.cpp
    ${IMATISTL_SOUCE_DIR}/src/Kernel/point.cpp
    ${IMATISTL_SOUCE_DIR}/src/Kernel/tmesh.cpp
    )

SET(MESHFIX_SRC
    #${IMATISTL_SOUCE_DIR}/src/MeshFix/meshfix.cpp
    )

SET(TMESH_SRC
    ${IMATISTL_SOUCE_DIR}/src/TMesh/edge.cpp
    ${IMATISTL_SOUCE_DIR}/src/TMesh/edgeHeap.cpp
    ${IMATISTL_SOUCE_DIR}/src/TMesh/io.cpp
    ${IMATISTL_SOUCE_DIR}/src/TMesh/tin.cpp
    ${IMATISTL_SOUCE_DIR}/src/TMesh/triangle.cpp
    ${IMATISTL_SOUCE_DIR}/src/TMesh/vertex.cpp
    )

ADD_LIBRARY(ImatiSTL
    ${ALGORITHM_SRC}
    ${KERNEL_INC} ${KERNEL_SRC}
    ${TMESH_INC} ${TMESH_SRC}
    ${MESHFIX_INC} ${MESHFIX_SRC}
    ${IMATISTL_INC} ${IMATISTL_SRC}
    )