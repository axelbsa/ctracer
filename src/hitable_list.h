#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "aabb.h"
#include "sphere.h"

typedef struct HitableListClass
{
    Sphere *list;
    int list_size;

}HittableList;

// HittableListClass above can't have just sphere list
// What about other primitives? Change it to an list of objects
// That will waste some space but ... can't have'em all
typedef struct object
{
    int object_type;
    union {
        Sphere sp;
        AABB bounding_box;
    };

}Object;

bool hittable_list_hit(HittableList hl, Ray r, float tmin, float tmax, HitRecord *rec);
bool hittable_bounding_box(HittableList  hl, double time0, double time1, AABB output_box);

#endif  /* HITABLE_H */
