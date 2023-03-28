#include "bvh.h"
#include "aabb.h"

int box_x_compare(const void * a, const void * b)
{
    AABB box_left;
    AABB box_right;

    HittableList *ah = *(HittableList **)a;
    HittableList *bh = *(HittableList **)b;

    if ( !hittable_bounding_box(*ah, 0, 0, &box_left) ||
         !hittable_bounding_box(*bh, 0, 0, &box_right))
    {
        fprintf(stderr, "Error: no bounding box found\n");
    }

    if (box_left.minimum.x - box_right.minimum.x < 0.0)
    {
        return -1;
    }
    return 1;
}

int box_y_compare(const void * a, const void * b)
{
    AABB box_left;
    AABB box_right;

    HittableList *ah = *(HittableList **)a;
    HittableList *bh = *(HittableList **)b;

    if ( !hittable_bounding_box(*ah, 0, 0, &box_left) ||
         !hittable_bounding_box(*bh, 0, 0, &box_right))
    {
        fprintf(stderr, "Error: no bounding box found\n");
    }

    if (box_left.minimum.y - box_right.minimum.y < 0.0)
    {
        return -1;
    }
    return 1;
}

int box_z_compare(const void * a, const void * b)
{
    AABB box_left;
    AABB box_right;

    HittableList *ah = *(HittableList **)a;
    HittableList *bh = *(HittableList **)b;

    if ( !hittable_bounding_box(*ah, 0, 0, &box_left) ||
         !hittable_bounding_box(*bh, 0, 0, &box_right))
    {
        fprintf(stderr, "Error: no bounding box found\n");
    }

    if (box_left.minimum.z - box_right.minimum.z < 0.0)
    {
        return -1;
    }
    return 1;
}

void bvh_create_node(bvh_node *b_node, HittableList **l,const int n, float time0, float time1)
{
    const int axis = (int)(3 * drand48());

    switch(axis)
    {
        case 0:
            qsort(l, n, sizeof(HittableList *), box_x_compare);
            break;

        case 1:
            qsort(l, n, sizeof(HittableList *), box_y_compare);
            break;

        case 2:
            qsort(l, n, sizeof(HittableList *), box_z_compare);
            break;
    };

    if (n == 1)
    {
        b_node->left = l[0]->objects;
        b_node->right = l[0]->objects;
    }
    else if (n == 2)
    {
        b_node->left = l[0]->objects;
        b_node->left = l[1]->objects;
    }
    else
    {
        struct bvh_node *left = malloc(sizeof(struct bvh_node));
        struct bvh_node *right = malloc(sizeof(struct bvh_node));
        //b_node->left = left->left;
        bvh_create_node(left, l, n / 2, time0, time1);

        //b_node->right;
        bvh_create_node(right, l + n / 2, n - n / 2, time0, time1);
    }

    //bvh_node_bounding_box(bvh_node b_node, double time0, double time1, AABB *output_box)
    AABB box_left;
    AABB box_right;

    //bool left_box = bvh_node_bounding_box(b_node->left, time0, time1, &box_left);
    //bool right_box = bvh_node_bounding_box(b_node->right, time0, time1, &box_left);

    //if ()

    //surrounding_box()

    //b_node.box = :
}
