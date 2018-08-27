CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project(ImatiSTL_test)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive -DIS64BITPLATFORM")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")

set(IMATISTL_SOUCE_DIR external/ImatiSTL)
include(external/ImatiSTL.cmake)

include_directories(external/libigl/include)
include_directories(external/eigen-git-mirror)

include_directories(include)
add_executable(imatistl_test test/ImatiSTL.cpp)
target_link_libraries(imatistl_test ImatiSTL)
