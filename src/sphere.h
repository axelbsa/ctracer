#ifndef SPHERE_H
#define SPHERE_H

#include "aabb.h"
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
bool sphere_hit_simple(Sphere sp, Ray r, double t_min, double t_max, HitRecord *rec);
bool bounding_box(Sphere sp, double time0, double time1, AABB output_box);


#endif  /* Sphere */
