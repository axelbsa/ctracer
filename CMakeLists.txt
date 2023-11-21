cmake_minimum_required (VERSION 2.8.12)

project(ctracer)

# Create a sources variable with a link to all cpp files to compile
#set(SOURCES
#    src/main.c
#    src/vec3.c
#    src/ray.c
#    src/material.c
#    src/sphere.c
#    src/hitable_list.c
#    src/camera.c
#    src/common.c
#)

file(GLOB_RECURSE src_files ${CMAKE_CURRENT_LIST_DIR}/src/*.[ch])

#add_executable(${PROJECT_NAME} src/main.c src/vec3.c src/ray.c src/material.c src/sphere.c src/hitable_list.c src/camera.c src/common.c)
add_executable(${PROJECT_NAME}  ${src_files} src/aabb.h src/aabb.c src/bvh.h src/bvh.c src/triangle.c src/triangle.h)
target_link_libraries(${PROJECT_NAME} m)
