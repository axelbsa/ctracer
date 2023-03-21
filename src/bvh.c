#include "bvh.h"

int _box_x_compare(const void * a, const void * b)
{
    AABB box_left;
    AABB box_right;

    HittableList *ah = *(HittableList **)a;
    HittableList *bh = *(HittableList **)b;

    //if (ah->objects->bounding_box


    return 0;
}

int _box_y_compare(const void * a, const void * b)
{
    return 0;
}

int _box_z_compare(const void * a, const void * b)
{
    return 0;
}

Object * bvh_create_node(bvh_node b_node, HittableList **l,const int n, float time0, float time1)
{
    const int axis = (int)(3 * drand48());

    switch(axis)
    {
        case 0:
            qsort(l, n, sizeof(HittableList *), _box_x_compare);
            break;

        case 1:
            qsort(l, n, sizeof(HittableList *), _box_y_compare);
            break;

        case 2:
            qsort(l, n, sizeof(HittableList *), _box_z_compare);
            break;
    };

    if (n == 1)
    {
        b_node.left = l[0]->objects;
        b_node.right = l[0]->objects;
    }
    else if (n == 2)
    {
        b_node.left = l[0]->objects;
        b_node.left = l[1]->objects;
    }
    else
    {
        b_node.left = bvh_create_node(b_node, l, n / 2, time0, time1);
        b_node.right = bvh_create_node(b_node, l + n / 2, n - n / 2, time0, time1);
    }
}
