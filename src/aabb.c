//
// Created by axelbs on 19.03.2023.
//

#include <stdbool.h>

#include "aabb.h"
#include "ray.h"

bool aabb_hit(AABB aabb, Ray r, double t_min, double t_max)
{

    // Test for x
    float t0_x = MIN(
            (aabb.minimum.x - origin(r).x) / direction(r).x,
            (aabb.maximum.x - origin(r).x) / direction(r).x
    );

    float t1_x = MAX(
            (aabb.minimum.x - origin(r).x) / direction(r).x,
            (aabb.maximum.x - origin(r).x) / direction(r).x
    );

    t_min = MAX(t0_x, t_min);
    t_max = MIN(t1_x, t_max);

    if (t_max <= t_min)
        return false;

    // Test for y
    float t0_y = MIN(
            (aabb.minimum.y - origin(r).y) / direction(r).y,
            (aabb.maximum.y - origin(r).y) / direction(r).y
    );

    float t1_y = MAX(
            (aabb.minimum.y - origin(r).y) / direction(r).y,
            (aabb.maximum.y - origin(r).y) / direction(r).y
    );

    t_min = MAX(t0_y, t_min);
    t_max = MIN(t1_y, t_max);

    if (t_max <= t_min)
        return false;

    // Test for z
    float t0_z = MIN(
            (aabb.minimum.z - origin(r).z) / direction(r).z,
            (aabb.maximum.z - origin(r).z) / direction(r).z
    );

    float t1_z = MAX(
            (aabb.minimum.z - origin(r).z) / direction(r).z,
            (aabb.maximum.z - origin(r).z) / direction(r).z
    );

    t_min = MAX(t0_z, t_min);
    t_max = MIN(t1_z, t_max);

    if (t_max <= t_min)
        return false;

    // Nothing left to test, return true
    return true;
}