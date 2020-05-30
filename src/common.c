#include <stdlib.h>
#include <time.h>

#include "vec3.h"

double random_double()
{
    //return (double)rand() / (double)((unsigned)RAND_MAX + 1.0);
    return rand() / (RAND_MAX + 1.0);
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
