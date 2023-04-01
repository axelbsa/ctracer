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
    //Sphere *list;
    struct Object *objects;
    int list_size;

}HittableList;

typedef struct HitableListBvhClass
{
    Sphere *list;
    struct bvh_node *objects;
    int list_size;

}HittableListBVH;

bool hittable_list_hit(HittableList hl, Ray r, float tmin, float tmax, HitRecord *rec);
bool hittable_bounding_box(HittableListBVH hl, double time0, double time1, AABB *output_box);

#endif  /* HITABLE_H */
