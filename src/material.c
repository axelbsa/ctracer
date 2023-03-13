#include <stdbool.h>

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "common.h"

int lambertian_scatter(
        Ray r_in, HitRecord rec, Vec3 *attenuation,
        Ray *scattered, Vec3 albedo)
{

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
    Vec3 fuzziness = vec3_const_mul(random_in_unit_sphere(), rec.mat_ptr->fuzz);
    reflected = vec3_add(reflected, fuzziness);
    Ray _tmp = {.A = rec.p, .B = reflected};
    *scattered = _tmp;
    *attenuation = albedo;

    return ( dot( direction(*scattered), rec.normal) > 0 );
}


int dielectric_scatter(
        Ray r_in, HitRecord rec, Vec3 *attenuation,
        Ray *scattered, Vec3 albedo)
{
    *attenuation = vec3(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / rec.mat_ptr->ir) : rec.mat_ptr->ir;

    //vec3 unit_direction = unit_vector(r_in.direction());
    Vec3 unit_direction = unit_vector(direction(r_in));

    //vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);
    Vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);

    //scattered = ray(rec.p, refracted);
    Ray _scattered_ray = {.A = rec.p, .B = refracted};
    *scattered = _scattered_ray;
    return true;
}
