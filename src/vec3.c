#include <stdbool.h>
#include <math.h>

#include "common.h"
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

Vec3* vec3_negate_ptr(Vec3* v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
    return v;  // Why am i mutating values _and_ then returning the address?
}

Vec3 vec3_negate(Vec3 v)
{
    return vec3(-v.x, -v.y, -v.z);
}

Vec3 random_in_unit_disc()
{
    while (true)
    {
        Vec3 p = vec3(random_double(-1,1), random_double(-1,1), 0);

        if (square_length(p) >= 1)
        {
            continue;
        }

        return p;
    }

}

Vec3 cross(const Vec3 u, const Vec3 v)
{
    return vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}


float dot(Vec3 a, Vec3 b)
{
    return (
        (a.x * b.x) +
        (a.y * b.y) +
        (a.z * b.z)
    );
}


float length(Vec3 v)
{
    return sqrtf(
        v.x * v.x +
        v.y * v.y +
        v.z * v.z
    );
}

double length_squared(Vec3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}


Vec3 unit_vector(Vec3 v)
{
    return vec3_const_div(v, length(v));
}


Vec3 vec3(float a, float b, float c)
{
    Vec3 v3 = {a, b, c};
    return v3;
}

Vec3 reflect(Vec3 v, Vec3 n)
{
    float _tmp = 2 * dot(v, n);
    Vec3 two_dot = vec3_const_mul(n, _tmp);
    Vec3 result = vec3_sub(v, two_dot);
    return result;
}

Vec3 refract(Vec3 uv, Vec3 n, double etai_over_etat)
{
    float cos_theta = dot(vec3_negate(uv), n);
    cos_theta = MIN(cos_theta, 1.0f);

    Vec3 r_out_perp = vec3_const_mul(n, cos_theta);
    r_out_perp = vec3_add(uv, r_out_perp);
    r_out_perp = vec3_const_mul(r_out_perp, etai_over_etat);

    float r_out_parallel_fabs = -sqrtf( fabsf(1.0f - length(r_out_perp)) );
    Vec3 r_out_parallel = vec3_const_mul(n, r_out_parallel_fabs);

    return vec3_add(r_out_perp, r_out_parallel);
}

/*vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
auto cos_theta = fmin(dot(-uv, n), 1.0);
vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
return r_out_perp + r_out_parallel;
}*/

bool refract_2(Vec3 v, Vec3 n, float ni_over_nt, Vec3* refracted)
{
    Vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);

    if (discriminant > 0)
    {
        // refracted = ni_over_nt * (uv - n*dt) - n*qrt(discriminant);
        Vec3 ref_left_part = vec3_const_mul(n, dt);
        ref_left_part = vec3_sub(uv, ref_left_part);
        ref_left_part = vec3_const_mul(ref_left_part, ni_over_nt);

        Vec3 ref_right_part = vec3_const_mul(n, sqrtf(discriminant));

        *refracted = vec3_sub(ref_left_part, ref_right_part);
        return true;
    }

    return false;

}


float square_length(Vec3 v1)
{
    return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

double degrees_to_radians(double degrees) {
#ifndef M_PI
    const double pi = 3.1415926535897932385;
    return degrees * pi / 180.0;
#else
    return degrees * M_PI / 180.0;
#endif

}