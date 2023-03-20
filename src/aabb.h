#ifndef CTRACER_AABB_H
#define CTRACER_AABB_H

#include "ray.h"
#include "vec3.h"

typedef struct aabb {
    Vec3 minimum;
    Vec3 maximum;
}AABB;


bool aabb_hit(AABB aabb, Ray r, double t_min, double t_max);

#endif //CTRACER_AABB_H
