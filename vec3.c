#include <math.h>

#include "vec3.h"


Vec3 vec3_add(Vec3 v1, Vec3 v2)
{
    Vec3 res = {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z,
    };
    return res;
}


Vec3 vec3_sub(Vec3 v1, Vec3 v2)
{
    Vec3 res = {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z,
    };
    return res;
}


Vec3 vec3_mul(Vec3 v1, Vec3 v2)
{
    Vec3 res = {
        v1.x * v2.x,
        v1.y * v2.y,
        v1.z * v2.z,
    };
    return res;
}


Vec3 vec3_div(Vec3 v1, Vec3 v2)
{
    Vec3 res = {
        v1.x / v2.x,
        v1.y / v2.y,
        v1.z / v2.z,
    };
    return res;
}


Vec3 vec3_const_add(Vec3 v1, const float t)
{
    Vec3 res = {
        v1.x + t,
        v1.y + t,
        v1.z + t,
    };
    return res;
}


Vec3 vec3_const_sub(Vec3 v1, const float t)
{
    Vec3 res = {
        v1.x - t,
        v1.y - t,
        v1.z - t,
    };
    return res;
}


Vec3 vec3_const_mul(Vec3 v1, const float t)
{
    Vec3 res = {
        t * v1.x,
        t * v1.y,
        t * v1.z,
    };
    return res;
}


Vec3 vec3_const_div(Vec3 v1, const float t)
{
    Vec3 res = {
        v1.x / t,
        v1.y / t,
        v1.z / t,
    };
    return res;
}


float dot(Vec3 a, Vec3 b)
{
    return (
        a.x * b.x +
        a.y * b.y +
        a.z * b.z
    );
}


float length(Vec3 v)
{
    return sqrt(
        v.x * v.x +
        v.y * v.y +
        v.z * v.z
    );
}


Vec3 unit_vector(Vec3 v)
{
    return vec3_const_div(v, length(v));
}


Vec3 vec3(float a, float b, float c)
{
    Vec3 foo = {a, b, c};
    return foo;
}


float square_length(Vec3 v1)
{
    return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}



