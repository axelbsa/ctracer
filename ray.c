#include "ray.h"
#include "vec3.h"


Vec3 origin(Ray r)
{
    return r.A;
}


Vec3 direction(Ray r)
{
    return r.B;
}


Vec3 point_at_parameter(Ray r, float t)
{
    Vec3 temp = vec3_const_mul(r.B, t);
    return vec3_add(r.A, temp);
}
