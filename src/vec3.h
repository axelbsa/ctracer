#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>

typedef struct vector3
{
    float x;
    float y; 
    float z;

}Vec3;

Vec3 vec3(float a, float b, float c);  // Creates a new Vec3

Vec3 vec3_add(Vec3 v1, Vec3 v2);
Vec3 vec3_sub(Vec3 v1, Vec3 v2);
Vec3 vec3_mul(Vec3 v1, Vec3 v2);
Vec3 vec3_div(Vec3 v1, Vec3 v2);

Vec3 vec3_const_add(Vec3 v1, const float t);
Vec3 vec3_const_sub(Vec3 v1, const float t);
Vec3 vec3_const_mul(Vec3 v1, const float t);
Vec3 vec3_const_div(Vec3 v1, const float t);

Vec3 vec3_negate(Vec3 v);
Vec3* vec3_negate_ptr(Vec3* v);

Vec3 vec3_random();
Vec3 vec3_random_mm(double min, double max);

Vec3 unit_vector(Vec3 v);
Vec3 reflect(Vec3 v, Vec3 n);
Vec3 cross(const Vec3 u, const Vec3 v);
Vec3 random_in_unit_disc();
Vec3 refract(Vec3 uv, Vec3 n, double etai_over_etat);
bool refract_2(Vec3 v, Vec3 n, float ni_over_nt, Vec3* refracted);

float dot(Vec3 a, Vec3 b);
float length(Vec3 v);
float square_length(Vec3 v1);
double degrees_to_radians(double degrees);

#endif  /* VEC3_H */
