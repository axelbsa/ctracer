#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "vec3.h"
#include "material.h"

typedef struct SphereObject
{
    Vec3 center;
    float radius;
    struct material *mat_ptr;
    Vec3 albedo;
}Sphere;

bool sphere_hit(Sphere sp, Ray r, float tmin, float tmax, HitRecord *rec);


#endif  /* Sphere */
