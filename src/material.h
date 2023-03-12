#ifndef MAT_H
#define MAT_H

#include "ray.h"

typedef struct 
{
    float t;
    Vec3 p;
    Vec3 normal;
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
    Scatter s;
    Vec3 albedo;
    double fuzz;
}Material;

int lambertian_scatter(Ray r_in, HitRecord rec, Vec3 *attenuation, Ray *scattered, Vec3 albedo);
int metal_scatter(Ray r_in, HitRecord rec, Vec3 *attenuation, Ray *scattered, Vec3 albedo);

#endif
