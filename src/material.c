#include <stdbool.h>
#include <math.h>

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "common.h"


double reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    // Copy pasted directly from the book Raytracing in a weekend
    double r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

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

/*
int dielectric_scatter(
        Ray r_in, HitRecord rec, Vec3 *attenuation,
        Ray *scattered, Vec3 albedo)
{
    *attenuation = vec3(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / rec.mat_ptr->ir) : rec.mat_ptr->ir;

    Vec3 unit_direction = unit_vector(direction(r_in));

    //double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double cos_theta = MIN(dot(vec3_negate(unit_direction), rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
    {
        direction = reflect(unit_direction, rec.normal);
    }
    else
    {
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    }

    Ray _scattered_ray = {.A = rec.p, .B = direction};
    *scattered = _scattered_ray;
    return true;
}
*/


int dielectric_scatter_old(
        Ray r_in, HitRecord rec, Vec3 *attenuation,
        Ray *scattered, Vec3 albedo)
{
    float cosine;
    float reflect_prob;
    float ni_over_nt;

    Vec3 outward_normal;
    Vec3 reflected = reflect(direction(r_in), rec.normal);
    *attenuation = vec3(1.0f, 1.0f, 1.0f);
    Vec3 refracted = vec3(0.0f, 0.0f, 0.0f);

    if ( dot(direction(r_in), rec.normal) > 0 )
    {
        outward_normal = vec3_negate(rec.normal);
        ni_over_nt = rec.mat_ptr->ir;
        cosine = rec.mat_ptr->ir * dot(direction(r_in), rec.normal) / length(direction(r_in));
    }
    else
    {
        outward_normal = rec.normal;
        ni_over_nt = 1.0f / rec.mat_ptr->ir;
        cosine = -dot(direction(r_in), rec.normal) / length(direction(r_in));
    }

    if (refract_2(direction(r_in), outward_normal, ni_over_nt, &refracted))
    {
        reflect_prob = (float)reflectance(cosine, rec.mat_ptr->ir);
    }
    else
    {
        reflect_prob = 1.0f;
    }

    if (drand48() < reflect_prob)
    {
        Ray _scattered_ray = {.A = rec.p, .B = reflected};
        *scattered = _scattered_ray;
    }
    else
    {
        Ray _scattered_ray = {.A = rec.p, .B = refracted};
        *scattered = _scattered_ray;
    }

    return true;
}
