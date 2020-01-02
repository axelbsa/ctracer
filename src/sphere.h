#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "vec3.h"
#include "hitable.h"

typedef struct SphereObject
{
    Vec3 center;
    float radius;

}Sphere;

bool sphere_hit(Sphere sp, Ray r, float tmin, float tmax, HitRecord *rec);

#endif  /* Sphere */
