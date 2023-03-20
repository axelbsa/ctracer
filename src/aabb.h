#ifndef CTRACER_AABB_H
#define CTRACER_AABB_H

#include "ray.h"
#include "vec3.h"

typedef struct aabb {
    Vec3 minimum;
    Vec3 maximum;
}AABB;

static inline AABB surrounding_box(AABB box0, AABB box1) {
    Vec3 small = vec3(
            MIN(box0.minimum.x, box1.minimum.x),
            MIN(box0.minimum.y, box1.minimum.y),
            MIN(box0.minimum.z, box1.minimum.z)
    );

    Vec3 big = vec3(
            MAX(box0.maximum.x, box1.maximum.x),
            MAX(box0.maximum.y, box1.maximum.y),
            MAX(box0.maximum.z, box1.maximum.z)
    );

    AABB product = {.minimum = small, .maximum = big};
    return product;
}

bool aabb_hit(AABB aabb, Ray r, double t_min, double t_max);

#endif //CTRACER_AABB_H
