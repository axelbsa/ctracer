#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>
#include <math.h>

#ifdef _WIN32
#include "windows.h"
#else
#include <sys/time.h>
#endif

#include "common.h"

/*
 * drand48 for windows
 * https://gist.github.com/mortennobel/8665258
*/

#define RAND48_SEED_0   (0x330e)
#define RAND48_SEED_1 (0xabcd)
#define RAND48_SEED_2 (0x1234)
#define RAND48_MULT_0 (0xe66d)
#define RAND48_MULT_1 (0xdeec)
#define RAND48_MULT_2 (0x0005)
#define RAND48_ADD (0x000b)


typedef struct vector3
{
    float x;
    float y; 
    float z;

}Vec3;

static inline Vec3 vec3(float a, float b, float c);  // Creates a new Vec3

static inline Vec3 vec3_add(Vec3 v1, Vec3 v2);
static inline Vec3 vec3_sub(Vec3 v1, Vec3 v2);
static inline Vec3 vec3_mul(Vec3 v1, Vec3 v2);
static inline Vec3 vec3_div(Vec3 v1, Vec3 v2);

static inline Vec3 vec3_const_add(Vec3 v1, const float t);
static inline Vec3 vec3_const_sub(Vec3 v1, const float t);
static inline Vec3 vec3_const_mul(Vec3 v1, const float t);
static inline Vec3 vec3_const_div(Vec3 v1, const float t);

static inline Vec3 vec3_negate(Vec3 v);
static inline Vec3* vec3_negate_ptr(Vec3* v);

static inline Vec3 vec3_random();
static inline Vec3 vec3_random_mm(double min, double max);

static inline Vec3 unit_vector(Vec3 v);
static inline Vec3 reflect(Vec3 v, Vec3 n);
static inline Vec3 cross(const Vec3 u, const Vec3 v);
static inline Vec3 random_in_unit_disc();
static inline Vec3 refract(Vec3 uv, Vec3 n, double etai_over_etat);
static inline bool refract_2(Vec3 v, Vec3 n, float ni_over_nt, Vec3* refracted);

static inline float dot(Vec3 a, Vec3 b);
static inline float length(Vec3 v);
static inline float square_length(Vec3 v1);
static inline double degrees_to_radians(double degrees);

static inline double random_double();
static inline double random_double_mm(double min, double max);
static inline Vec3 random_in_unit_sphere();
static inline Vec3 random_unit_vector();
static inline double get_time();


static inline void _dorand48(unsigned short xseed[3]);
static inline double erand48(unsigned short xseed[3]);
static inline double drand48();
static inline void srand48(long seed);



double get_time()
{
#ifdef _WIN32
    return GetTickCount() / 1000.0;
#else
    struct timeval tv;

	gettimeofday(&tv, 0);

	return tv.tv_sec + tv.tv_usec * 1.0e-6;
#endif

}

static unsigned short _rand48_seed[3] = {
        RAND48_SEED_0,
        RAND48_SEED_1,
        RAND48_SEED_2
};
static unsigned short _rand48_mult[3] = {
        RAND48_MULT_0,
        RAND48_MULT_1,
        RAND48_MULT_2
};
static unsigned short _rand48_add = RAND48_ADD;

void _dorand48(unsigned short xseed[3])
{
    unsigned long accu;
    unsigned short temp[2];

    accu = (unsigned long)_rand48_mult[0] * (unsigned long)xseed[0] +
           (unsigned long)_rand48_add;
    temp[0] = (unsigned short)accu;
    accu >>= sizeof(unsigned short)* 8;
    accu += (unsigned long)_rand48_mult[0] * (unsigned long)xseed[1] +
            (unsigned long)_rand48_mult[1] * (unsigned long)xseed[0];
    temp[1] = (unsigned short)accu;
    accu >>= sizeof(unsigned short)* 8;
    accu += _rand48_mult[0] * xseed[2] + _rand48_mult[1] * xseed[1] + _rand48_mult[2] * xseed[0];
    xseed[0] = temp[0];
    xseed[1] = temp[1];
    xseed[2] = (unsigned short)accu;
}

double erand48(unsigned short xseed[3])
{
    _dorand48(xseed);
    return ldexp((double) xseed[0], -48) +
           ldexp((double) xseed[1], -32) +
           ldexp((double) xseed[2], -16);
}

double drand48(){
    return erand48(_rand48_seed);
}

void srand48(long seed){
    _rand48_seed[0] = RAND48_SEED_0;
    _rand48_seed[1] = (unsigned short)seed;
    _rand48_seed[2] = (unsigned short)(seed >> 16);
    _rand48_mult[0] = RAND48_MULT_0;
    _rand48_mult[1] = RAND48_MULT_1;
    _rand48_mult[2] = RAND48_MULT_2;
    _rand48_add = RAND48_ADD;
}

double random_double()
{
    //return (double)rand() / (double)((unsigned)RAND_MAX + 1.0);
    return drand48();
}

double random_double_mm(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

Vec3 random_in_unit_sphere()
{
    Vec3 p;

    do
    {
        p = vec3(random_double(), random_double(), random_double());
        p = vec3_const_mul(p, 1.2);
        p = vec3_sub(p, vec3(1.0, 1.0, 1.0));

    } while( square_length(p) >= 1.0 );

    //fprintf(stderr, "Square length < 1.0: %f ", square_length(p));

    return p;
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}


static inline Vec3 vec3_sub(Vec3 v1, Vec3 v2)
{
    Vec3 res = {
            v1.x - v2.x,
            v1.y - v2.y,
            v1.z - v2.z,
    };
    return res;
}


static inline Vec3 vec3_add(Vec3 v1, Vec3 v2)
{
    Vec3 res = {
            v1.x + v2.x,
            v1.y + v2.y,
            v1.z + v2.z,
    };
    return res;
}




static inline Vec3 vec3_mul(Vec3 v1, Vec3 v2)
{
    Vec3 res = {
            v1.x * v2.x,
            v1.y * v2.y,
            v1.z * v2.z,
    };
    return res;
}


static inline Vec3 vec3_div(Vec3 v1, Vec3 v2)
{
    Vec3 res = {
            v1.x / v2.x,
            v1.y / v2.y,
            v1.z / v2.z,
    };
    return res;
}


static inline Vec3 vec3_const_add(Vec3 v1, const float t)
{
    Vec3 res = {
            v1.x + t,
            v1.y + t,
            v1.z + t,
    };
    return res;
}


static inline Vec3 vec3_const_sub(Vec3 v1, const float t)
{
    Vec3 res = {
            v1.x - t,
            v1.y - t,
            v1.z - t,
    };
    return res;
}


static inline Vec3 vec3_const_mul(Vec3 v1, const float t)
{
    Vec3 res = {
            t * v1.x,
            t * v1.y,
            t * v1.z,
    };
    return res;
}


static inline Vec3 vec3_const_div(Vec3 v1, const float t)
{
    Vec3 res = {
            v1.x / t,
            v1.y / t,
            v1.z / t,
    };
    return res;
}

static inline Vec3* vec3_negate_ptr(Vec3* v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
    return v;  // Why am i mutating values _and_ then returning the address?
}

static inline Vec3 vec3_negate(Vec3 v)
{
    return vec3(-v.x, -v.y, -v.z);
}

static inline Vec3 vec3_random()
{
    return vec3(random_double(), random_double(), random_double());
}

static inline Vec3 vec3_random_mm(double min, double max)
{
    return vec3(random_double_mm(min, max), random_double_mm(min, max), random_double_mm(min, max));
}

static inline Vec3 random_in_unit_disc()
{
    while (true)
    {
        Vec3 p = vec3(random_double_mm(-1,1), random_double_mm(-1,1), 0);

        if (square_length(p) >= 1)
        {
            continue;
        }

        return p;
    }

}

static inline Vec3 cross(const Vec3 u, const Vec3 v)
{
    return vec3(
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x
    );
}


static inline float dot(Vec3 a, Vec3 b)
{
    return (
            (a.x * b.x) +
            (a.y * b.y) +
            (a.z * b.z)
    );
}


static inline float length(Vec3 v)
{
    return sqrtf(
            v.x * v.x +
            v.y * v.y +
            v.z * v.z
    );
}

static inline double length_squared(Vec3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}


static inline Vec3 unit_vector(Vec3 v)
{
    return vec3_const_div(v, length(v));
}


Vec3 vec3(float a, float b, float c)
{
    Vec3 v3 = {a, b, c};
    return v3;
}

static inline Vec3 reflect(Vec3 v, Vec3 n)
{
    float _tmp = 2 * dot(v, n);
    Vec3 two_dot = vec3_const_mul(n, _tmp);
    Vec3 result = vec3_sub(v, two_dot);
    return result;
}

static inline Vec3 refract(Vec3 uv, Vec3 n, double etai_over_etat)
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

/* This is the version from the old book.
 * It calculates the normals on each pass, making it slightly slower,
 * but pre-calculating them ended up bogus in the sphere::hit()
 * */
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


static inline float square_length(Vec3 v1)
{
    return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

static inline double degrees_to_radians(double degrees) {
#ifndef M_PI
    const double pi = 3.1415926535897932385;
    return degrees * pi / 180.0;
#else
    return degrees * M_PI / 180.0;
#endif

}

#endif  /* VEC3_H */
