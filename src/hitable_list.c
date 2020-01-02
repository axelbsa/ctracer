#include <stdbool.h>

#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"


bool hittable_list_hit(HittableList hl, Ray r, float tmin, float tmax, HitRecord *rec)
{
    Vec3 p = vec3(0.0, 0.0, 0.0);
    HitRecord temp_rec = {
        .normal.x = 0.0, .normal.y = 0.0, .normal.z = 0.0, .t = 0.0, .p = p
    };
    bool hit_anything = false;
    double closest_so_far = tmax;

    for (int i = 0; i < hl.list_size; i++)
    {
        Sphere sphere = hl.list[i];
        bool hit = sphere_hit(sphere, r, tmin, closest_so_far, &temp_rec);

        if ( hit )
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }
    return hit_anything;
}
