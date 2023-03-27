#include <stdio.h>
#include <stdbool.h>

#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"

bool hittable_bounding_box(HittableList  hl, double time0, double time1, AABB *output_box)
{

    AABB temp_box;
    bool first_box = true;

    for (int i = 0; i < hl.list_size; i++)
    {
        int object_type = hl.objects[i].object_type;

        switch(object_type) {
            case 1: {
                Sphere sphere = hl.objects[i].sphere;
                bool hit = bounding_box(sphere, time0, time1, &temp_box);

                if ( !hit )
                {
                    return false;
                }

                *output_box = first_box ? temp_box : surrounding_box(*output_box, temp_box);
                first_box = false;

                break;
            }
            case 2: {
            }
            default:
                break;
        }

    }

    return true;

}


bool hittable_list_hit(HittableList hl, Ray r, float tmin, float tmax, HitRecord *rec)
{
    //fprintf(stderr, "Entering hitable list hit\n");

    Vec3 p = vec3(0.0, 0.0, 0.0);
    HitRecord temp_rec = {
        .normal.x = 0.0, .normal.y = 0.0, .normal.z = 0.0, .t = 0.0, .p = p
    };
    bool hit_anything = false;
    double closest_so_far = tmax;

    for (int i = 0; i < hl.list_size; i++)
    {
        bool hit = false;
        int object_type = hl.objects[i].object_type;

        switch(object_type) {
            case 1: {
                Sphere sphere = hl.objects[i].sphere;
                hit = sphere_hit_simple(sphere, r, tmin, closest_so_far, &temp_rec);
                break;
            }
            case 2: {
                //AABB bounding_box = hl.objects[i].bounding_box;
                //hit = aabb_hit(bounding_box, r, tmin, closest_so_far);
                break;
            }
            default:
                // This should not happen, so here we should probably log an error!
                break;
        }
        //fprintf(stderr, "HL.list index = %d\n", i);
        //fprintf(stderr, "Done sphere hit\n");

        if ( hit )
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }
    return hit_anything;
}
