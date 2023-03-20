#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "ray.h"
#include "vec3.h"
#include "material.h"
#include "sphere.h"


static inline void _set_face_normal(Ray r, Vec3 outward_normal, HitRecord *rec)
{
    //front_face = dot(r.direction(), outward_normal) < 0;
    rec->front_face = dot(direction(r), outward_normal) < 0;

    //normal = front_face ? outward_normal : -outward_normal;
    rec->normal = rec->front_face ? outward_normal : vec3_negate(outward_normal);
}

bool bounding_box(Sphere sp, double time0, double time1, AABB output_box)
{

    AABB _out = {
            .minimum = vec3_sub(sp.center, vec3(sp.radius, sp.radius, sp.radius)),
            .maximum = vec3_add(sp.center, vec3(sp.radius, sp.radius, sp.radius))
    };
    output_box = _out;
    return true;

}

bool sphere_hit_simple(Sphere sp, Ray r, double t_min, double t_max, HitRecord *rec)
{
    Vec3 oc = vec3_sub(origin(r), sp.center);
    float a = square_length(direction(r));
    float half_b = dot(oc, direction(r));
    float c = square_length(oc) - sp.radius * sp.radius;

    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
    {
        return false;
    }

    float sqrtd = sqrtf(discriminant);
    double root = (-half_b - sqrtd) / a;

    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;  // Second solution for the quadratic
        if (root < t_min || t_max < root) // if ~ Still no solution to the equation
        {
            return false;
        }
    }

    rec->t = (float)root;
    rec->p = point_at_parameter(r, rec->t);
    rec->mat_ptr = sp.mat_ptr;

    // (rec.p - center) / radius;
    Vec3 _p_minus_center = vec3_sub(rec->p, sp.center);
    rec->normal = vec3_const_div(_p_minus_center, sp.radius);

    /* Calculating the front facing normal doesn't work, there is a bug somewhere.
     * luckily we can calculate the face normal in the material scatter functions,
     * though, we need to do that for each scatter function :/

    Vec3 _outward_normal = vec3_sub(rec->p, sp.center);
    _outward_normal = vec3_const_div(_outward_normal, sp.radius);
    rec->front_face = dot(direction(r), _outward_normal) < 0;
    rec->normal = rec->front_face ? _outward_normal : vec3_negate(_outward_normal);
    */

    return true;
}

bool sphere_hit(Sphere sp, Ray r, float tmin, float tmax, HitRecord *rec)
{
    //fprintf(stderr, "Found hit, entering sphere_hit\n");

    /* Quadratic formula for calculating x^2 * y^2 * z^2 */
    Vec3 oc = vec3_sub(origin(r), sp.center);
    float a = dot(direction(r), direction(r));
    float b = dot(oc, direction(r));
    float c = dot(oc, oc) - sp.radius*sp.radius;
    float discriminant = (b * b) - (a * c);
    //fprintf(stderr, "Sphere_hit: Starting if\n");

    if ( discriminant > 0 )
    {
        /* End of quadratic formula, probably faster to avoid squaring
         * until we actually have a "hit" */
        float root = (-b - sqrtf( discriminant )) / a;

        if ( root < tmax && root > tmin) 
        {
            rec->t = root;
            rec->p = point_at_parameter(r, rec->t);

            //fprintf(stderr, "Sphere_hit: found root -b \n");

            Vec3 temp = vec3_sub(rec->p, sp.center);
            rec->normal = vec3_const_div(temp, sp.radius);
            rec->mat_ptr = sp.mat_ptr;
            //fprintf(stderr, "\tSphere_hit: setting material \n");

            //Vec3 outward_normal = (rec->p - center) / radius;
            Vec3 _outward_normal = vec3_sub(rec->p, sp.center);
            _outward_normal = vec3_const_div(_outward_normal, sp.radius);
            //_set_face_normal(r, &_outward_normal, rec);

            return true;
        }
        
        /* Check second solution in quadratic formula -b +- sqrt */
        root = (-b + sqrtf( discriminant )) / a;
        if ( root < tmax && root > tmin)
        {
            rec->t = root;
            rec->p = point_at_parameter(r, rec->t);
            //fprintf(stderr, "Sphere_hit: found root +b \n");

            Vec3 temp = vec3_sub(rec->p, sp.center);
            rec->normal = vec3_const_div(temp, sp.radius);
            rec->mat_ptr = sp.mat_ptr;
            //fprintf(stderr, "\tSphere_hit: setting material \n");

            Vec3 _outward_normal = vec3_sub(rec->p, sp.center);
            _outward_normal = vec3_const_div(_outward_normal, sp.radius);
            //_set_face_normal(r, &_outward_normal, rec);

            return true;
        }
    
    }
    return false;
}
