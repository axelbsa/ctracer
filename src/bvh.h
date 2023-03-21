#ifndef CTRACER_BVH_H
#define CTRACER_BVH_H

#include <stdbool.h>
#include "hitable_list.h"


struct bvh_node{
    struct Object *left;
    struct Object *right;
    AABB box;
};

typedef struct bvh_node bvh_node;

static inline bool bvh_bounding_box(double time0, double time1, AABB *output_box);
static inline bool bvh_node_hit(bvh_node b_node, Ray r, double t_min, double t_max, HitRecord *rec);

bool bvh_node_bounding_box(bvh_node b_node, double time0, double time1, AABB *output_box)
{
    *output_box = b_node.box;
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
            hit_left = sphere_hit_simple(b_node.left->sphere, r, t_min, t_max, rec);
            break;
        case 2:
            hit_left = bvh_node_hit(*b_node.left->b_node, r, t_min, t_max, rec);
            break;
        default:
            break;
    };

    // Same checks, but for the right node
    int right_object_type = b_node.right->object_type;
    switch(right_object_type){
        case 1:
            hit_right = sphere_hit_simple(b_node.right->sphere, r, t_min, t_max, rec);
            break;
        case 2:
            hit_right = bvh_node_hit(*b_node.right->b_node, r, t_min, hit_left ? rec->t : t_max, rec);
            break;
        default:
            break;
    };

    return hit_left || hit_right;
}

#endif //CTRACER_BVH_H
