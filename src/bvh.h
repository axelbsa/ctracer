#ifndef CTRACER_BVH_H
#define CTRACER_BVH_H

#include <stdbool.h>
#include "hitable_list.h"


struct bvh_node{
    int object_type;
    struct Object value;
    struct bvh_node *left;
    struct bvh_node *right;
    AABB box;
};

typedef struct bvh_node bvh_node;

static inline bool bvh_node_bounding_box(Object *obj, double time0, double time1, AABB *output_box);
static inline bool bvh_node_hit(bvh_node b_node, Ray r, double t_min, double t_max, HitRecord *rec);
void bvh_create_node(bvh_node *b_node, HittableList **l, const int n, float time0, float time1);

static inline bool bvh_node_bounding_box(Object *obj, double time0, double time1, AABB *output_box)
{
    *output_box = obj->box;
    return true;
}


bool bvh_node_hit(bvh_node b_node, Ray r, double t_min, double t_max, HitRecord *rec)
{
    if ( !aabb_hit(b_node.box, r, t_min, t_max) )
        return false;

    bool hit_left = false;
    bool hit_right = false;

    int left_object_type = b_node.left->object_type;
    switch(left_object_type){
        case 1:
            hit_left = sphere_hit_simple(b_node.left->value.sphere, r, t_min, t_max, rec);
            break;
        case 2:
            hit_left = bvh_node_hit(*b_node.left, r, t_min, t_max, rec);
            break;
        default:
            break;
    };

    // Same checks, but for the right node
    int right_object_type = b_node.right->object_type;
    switch(right_object_type){
        case 1:
            hit_right = sphere_hit_simple(b_node.right->value.sphere, r, t_min, t_max, rec);
            break;
        case 2:
            hit_right = bvh_node_hit(*b_node.right, r, t_min, hit_left ? rec->t : t_max, rec);
            break;
        default:
            break;
    };

    return hit_left || hit_right;
}

#endif //CTRACER_BVH_H
