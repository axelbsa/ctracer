#include <stdbool.h>

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "common.h"

int lambertian_scatter(
        Ray r_in, HitRecord rec, Vec3 *attenuation,
        Ray *scattered, Vec3 albedo)
{


    //Vec3 target = vec3_add(rec.p, rec.normal);
    //Vec3 random_sphere = random_unit_vector();
    //target = vec3_add(target, random_sphere);
    //Ray temp = { rec.p, vec3_sub(target, rec.p) };

    //return vec3_const_mul( color(temp, world, depth - 1, p, rec), 0.5 );


    Vec3 target = vec3_add(rec.p, rec.normal);

    Vec3 random_sphere = random_unit_vector();
    target = vec3_add(target, random_sphere);

    //target = vec3_add(target, random_in_unit_sphere());
    
    Vec3 target_minus_rec = vec3_sub(target, rec.p);
    Ray _tmp = {.A = rec.p, .B = target_minus_rec};
    *scattered = _tmp;
    *attenuation = albedo;

    return true;
}

int metal_scatter(
        Ray r_in, HitRecord rec, Vec3 *attenuation,
        Ray *scattered, Vec3 albedo)
{
    Vec3 reflected = reflect(
            unit_vector( direction( r_in ) ),
            rec.normal
    );
    Ray _tmp = {.A = rec.p, .B = reflected};
    *scattered = _tmp;
    *attenuation = albedo;

    return ( dot( direction(*scattered), rec.normal) > 0 );
}
