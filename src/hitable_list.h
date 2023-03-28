#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "aabb.h"
#include "sphere.h"


// HittableListClass above can't have just sphere list
// What about other primitives? Change it to a list of objects
// That will waste some space but ... can't have'em all
struct Object
{
    int object_type;
    AABB box;
    union {
        Sphere sphere;
        struct bvh_node *b_node;
    };
};

typedef struct Object Object;

typedef struct HitableListClass
{
    Sphere *list;
    struct Object *objects;  // This should probably be changed to a bvh_node which has 2 object pointers
    int list_size;

}HittableList;

bool hittable_list_hit(HittableList hl, Ray r, float tmin, float tmax, HitRecord *rec);
bool hittable_bounding_box(HittableList  hl, double time0, double time1, AABB *output_box);

#endif  /* HITABLE_H */
