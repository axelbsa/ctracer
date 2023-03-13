#ifndef VEC3_H
#define VEC3_H

typedef struct vector3
{
    float x;
    float y; 
    float z;

}Vec3;

Vec3 vec3_add(Vec3 v1, Vec3 v2);
Vec3 vec3_sub(Vec3 v1, Vec3 v2);
Vec3 vec3_mul(Vec3 v1, Vec3 v2);
Vec3 vec3_div(Vec3 v1, Vec3 v2);

Vec3 vec3_const_add(Vec3 v1, const float t);
Vec3 vec3_const_sub(Vec3 v1, const float t);
Vec3 vec3_const_mul(Vec3 v1, const float t);
Vec3 vec3_const_div(Vec3 v1, const float t);

float dot(Vec3 a, Vec3 b);
float length(Vec3 v);
Vec3 unit_vector(Vec3 v);
Vec3 vec3(float a, float b, float c);
float square_length(Vec3 v1);
Vec3 reflect(Vec3 v, Vec3 n);
Vec3 refract(Vec3 uv, Vec3 n, double etai_over_etat);
Vec3* vec3_negate(Vec3* v);


#endif  /* VEC3_H */
