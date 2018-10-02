
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Particles_cloud)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Particles_cloud MACOSX_BUNDLE Particles_cloud.cxx)
 
target_link_libraries(Particles_cloud ${VTK_LIBRARIES})
