#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "ray.h"
#include "vec3.h"
#include "material.h"
#include "sphere.h"


void _set_face_normal(Ray r, Vec3* outward_normal, HitRecord *rec) {
    //front_face = dot(r.direction(), outward_normal) < 0;
    rec->front_face = dot(direction(r), *outward_normal) < 0;

    //normal = front_face ? outward_normal : -outward_normal;
    rec->normal = rec->front_face ? *outward_normal : vec3_negate(*outward_normal);
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
        float root = (-b - sqrt( discriminant )) / a;

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
        root = (-b + sqrt( discriminant )) / a;
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
