#include <stdbool.h>

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "common.h"

int lambertian_scatter(
        Ray r_in, HitRecord rec, Vec3 attenuation, 
        Ray scattered, Vec3 albedo)
{
    Vec3 target = vec3_add(rec.p, rec.normal);
    target = vec3_add(target, random_in_unit_sphere());
    
    Vec3 target_minus_rec = vec3_sub(target, rec.p);
    Ray r = {.A = rec.p, .B = target_minus_rec};
    albedo = attenuation;

    return true;
}

int metal_scatter(
        Ray r_in, HitRecord rec, 
        Vec3 attenuation, Ray scattered)
{
    return false;
}
