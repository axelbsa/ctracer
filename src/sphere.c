#include <math.h>
#include <stdbool.h>

#include "ray.h"
#include "vec3.h"
#include "material.h"
#include "sphere.h"


bool sphere_hit(Sphere sp, Ray r, float tmin, float tmax, HitRecord *rec)
{
    /* Quadratic formula for calculating x^2 * y^2 * z^2 */
    Vec3 oc = vec3_sub(origin(r), sp.center);
    float a = dot(direction(r), direction(r));
    float b = dot(oc, direction(r));
    float c = dot(oc, oc) - sp.radius*sp.radius;
    float discriminant = (b * b) - (a * c);

    if ( discriminant > 0 )
    {
        /* End of quadric formula, probably faster to avoid squaring
         * until we actually have a "hit" */
        float root = (-b - sqrt( discriminant )) / a;

        if ( root < tmax && root > tmin) 
        {
            rec->t = root;
            rec->p = point_at_parameter(r, rec->t);
            
            Vec3 temp = vec3_sub(rec->p, sp.center);
            rec->normal = vec3_const_div(temp, sp.radius);
            return true;
        }
        
        /* Check second solution in quadric formual -b +- sqrt */
        root = (-b + sqrt( discriminant )) / a;
        if ( root < tmax && root > tmin)
        {
            rec->t = root;
            rec->p = point_at_parameter(r, rec->t);
            
            Vec3 temp = vec3_sub(rec->p, sp.center);
            rec->normal = vec3_const_div(temp, sp.radius);
            return true;
        }
    
    }
    return false;
}
