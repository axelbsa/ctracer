#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "aabb.h"
#include "sphere.h"


// HittableListClass above can't have just sphere list
// What about other primitives? Change it to an list of objects
// That will waste some space but ... can't have'em all
typedef struct object
{
    int object_type;
    union {
        Sphere sphere;
        AABB bounding_box;
    };

}Object;

typedef struct HitableListClass
{
    Sphere *list;
    Object *objects;
    int list_size;

}HittableList;


bool hittable_list_hit(HittableList hl, Ray r, float tmin, float tmax, HitRecord *rec);
bool hittable_bounding_box(HittableList  hl, double time0, double time1, AABB *output_box);

#endif  /* HITABLE_H */
