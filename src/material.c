#include <stdbool.h>

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "common.h"

int lambertian_scatter(
        Ray r_in, HitRecord rec, 
        Vec3 attenuation, Ray scattered)
{
    Vec3 target = vec3_add(rec.p, rec.normal);
    target = random_in_unit_sphere();

    return false;
}

int metal_scatter(
        Ray r_in, HitRecord rec, 
        Vec3 attenuation, Ray scattered)
{
    return false;
}
