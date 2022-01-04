#define _XOPEN_SOURCE    /* ALWAYS BEFORE the include statement */
#include <float.h>  // Only used for FLT_MAX
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/*#define STB_IMAGE_WRITE_IMPLEMENTATION*/
/*#include "stb_image_write.h"*/

#include "ray.h"
#include "image.h"
#include "vec3.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "common.h"

#define nx 2000
#define ny 1000
#define ns 100


void debugCamera(Camera cam)
{
    fprintf(stderr, "Camera has: lower_left: [%f, %f, %f]\n", cam.lower_left_corner.x, cam.lower_left_corner.y, cam.lower_left_corner.z );
}


void debugVector(Vec3 v1)
{
    fprintf(stderr, "Vector has: [%f, %f, %f]\n", v1.x, v1.y, v1.z );
}

Vec3 color(Ray r, HittableList world, int depth)
{
    Vec3 p = vec3(0, 0, 0);
    Vec3 albedo = vec3(0, 0, 0);
    HitRecord rec = {.normal.x = 0.0, .normal.y = 0.0, .normal.z = 0.0, .p = p};
    if ( hittable_list_hit(world, r, 0.001, FLT_MAX, &rec))
    {
        Ray scattered;
        Vec3 attenuation;

        if (depth < 50 && rec.mat_ptr->s(r, rec, &attenuation, &scattered, albedo))
        {
            printf("We have a metal hit\n");
        }
        else
        {

        }

        /*
        Vec3 target = vec3_add(rec.p, rec.normal);
        Vec3 random_sphere = random_in_unit_sphere();

        target = vec3_add(target, random_sphere);
        Ray temp = { rec.p, vec3_sub(target, rec.p) };
        
        return vec3_const_mul( color(temp, world, depth + 1), 0.5 );
        */
        //return vec3_const_mul(vec3(rec.normal.x +1,rec.normal.y +1,rec.normal.z +1), 0.5);
    }
    else
    {
        Vec3 unit_direction = unit_vector(direction(r));
        float t = (unit_direction.y + 1.0) * 0.5;
        float distance = (1.0 - t);

        Vec3 identity = {1.0, 1.0, 1.0};
        Vec3 gradiant = {0.5, 0.7, 1.0};

        Vec3 v_distance = vec3_const_mul(identity, distance);
        Vec3 v_gradiant = vec3_const_mul(gradiant, t);
        return vec3_add(v_distance, v_gradiant);
    }
}


void draw_some_pixels(int* data)
{
    fprintf(stderr, "Entering draw_some_pixels() func\n");

    Material metal_material;
    metal_material.s = metal_scatter;

    Material lambert_material;
    lambert_material.s = lambertian_scatter;

    //Scatter = metal_scatter;

    int num_spheres = 2;
    Sphere sphere_small = {
        .center.x = 0.0,
        .center.y = 0.0,
        .center.z = -1.0,
        .radius = 0.5,
        .mat_ptr = &metal_material
    };

    Sphere sphere_big = {
        .center.x = 0.0,
        .center.y = -100.5,
        .center.z = -1.0,
        .radius = 100.0,
        .mat_ptr = &lambert_material
    };

    HittableList world;
    Sphere *s_list;
    s_list = (Sphere*)malloc(sizeof(Sphere) * num_spheres);
    
    s_list[0] = sphere_small;
    s_list[1] = sphere_big;
    world.list = s_list;
    world.list_size = num_spheres;

    Camera cam = create_camera();
    debugCamera(cam);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            Vec3 col = vec3(0.0, 0.0, 0.0);
            for ( int s = 0; s < ns; s++)
            {
                float u = ((float) i + (float)random_double()) / (float) nx;
                float v = ((float) j + (float)random_double()) / (float) ny;
                Ray r = get_ray(cam, u, v);
                col = vec3_add(col, color(r, world, 0));
            }

            col = vec3_const_div(col, ns);
            col = vec3( sqrt(col.x), sqrt(col.y), sqrt(col.z) );

            int ir = (int) (255.99f * col.x);
            int ig = (int) (255.99f * col.y);
            int ib = (int) (255.99f * col.z);

            int index = (j * nx) + i;
            //fprintf(stderr, "[(i)=%d, (j)=%d   Index = %03d]   ", j, i, index);
            data[index] = (0xff << 24) | (ib << 16) | (ig << 8) | ir;
        }
        //fprintf(stderr, "\n");
    }

    free(s_list);
    fprintf(stderr, "Leaving draw_some_pixels()\n");
}


int main()
{
    //srand48(time(NULL));
    setvbuf(stdout, 0, _IOLBF, 4096);
    int* data;
    data = (int*)malloc(sizeof(uint32_t) * nx * ny);

    if ( data == NULL ) 
    {
        fprintf(stderr, "Some tragic shit happend while allocating memory\n");
        return EXIT_FAILURE;
    }

    //stbi_flip_vertically_on_write(-1); // flag is non-zero to flip data vertically

    draw_some_pixels(data);
    draw_image(data, nx * ny, nx, ny);

    free(data);

    return EXIT_SUCCESS;
}
