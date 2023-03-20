#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray 
{
    Vec3 A;
    Vec3 B;
    double time;
}Ray;

Vec3 origin(Ray r);
Vec3 direction(Ray r);
Vec3 point_at_parameter(Ray r, float t);

#endif  /* RAY */
