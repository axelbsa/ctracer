#ifndef MAT_H
#define MAT_H

#include <stdbool.h>
#include "ray.h"

typedef struct 
{
    float t;
    Vec3 p;
    Vec3 normal;
    //bool front_face;
    struct material *mat_ptr;
}HitRecord;


typedef int (*Scatter) ( 
        Ray r_in,
        HitRecord rec,
        Vec3 *attenuation,
        Ray *scattered,
        Vec3 albedo
);

typedef struct material {
    Scatter s;  // Scatter function, this field need to be populated for all material types
    Vec3 albedo;  // This the color for the material object, should only be here, not in the scatter functions
    double fuzz;  // Fuzziness factor, needed for metal objects
    double ir; // Refraction index, needed for dielectric objects
}Material;

int lambertian_scatter(Ray r_in, HitRecord rec, Vec3 *attenuation, Ray *scattered, Vec3 albedo);
int metal_scatter(Ray r_in, HitRecord rec, Vec3 *attenuation, Ray *scattered, Vec3 albedo);
int dielectric_scatter(Ray r_in, HitRecord rec, Vec3 *attenuation, Ray *scattered, Vec3 albedo);
int dielectric_scatter_old(Ray r_in, HitRecord rec, Vec3 *attenuation, Ray *scattered, Vec3 albedo);

#endif
