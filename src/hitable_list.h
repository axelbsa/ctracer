#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "sphere.h"

typedef struct HitableListClass
{
    Sphere *list;
    int list_size;

}HittableList;

bool hittable_list_hit(HittableList hl, Ray r, float tmin, float tmax, HitRecord *rec);

#endif  /* HITABLE_H */
