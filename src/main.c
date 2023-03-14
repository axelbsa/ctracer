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
#include "material.h"

#define nx 1000
#define ny 500
#define ns 50


void debugCamera(Camera cam)
{
    fprintf(
        stderr,
        "Camera has: lower_left: [%f, %f, %f]\n",
        cam.lower_left_corner.x,
        cam.lower_left_corner.y,
        cam.lower_left_corner.z
    );
}


void debugVector(Vec3 v1)
{
    fprintf(stderr, "Vector has: [%f, %f, %f]\n", v1.x, v1.y, v1.z );
}

Vec3 color(Ray r, HittableList world, int depth, Vec3 p, HitRecord rec)
{

    // Dont know, but to be sure, lets reinitialize rec
    rec.normal = vec3(0.0f, 0.0f, 0.0f);
    //rec.t = 0.0f;
    rec.p = p;

    if (depth <= 0) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    if ( hittable_list_hit(world, r, 0.001, FLT_MAX, &rec))
    {
        Ray scattered;
        Vec3 attenuation;

        if (rec.mat_ptr->s(r, rec, &attenuation, &scattered, rec.mat_ptr->albedo) )
        {
            //return attenuation * ray_color(scattered, world, depth-1);
            return vec3_mul(attenuation, color(scattered, world, depth-1, p, rec) );
        }

        return vec3(0.0f,0.0f,0.0f);

        //fprintf(stderr, "Entering draw_some_pixels() func\n");
        //Vec3 target = vec3_add(rec.p, rec.normal);
        //Vec3 random_sphere = random_unit_vector();
        //target = vec3_add(target, random_sphere);
        //Ray temp = { rec.p, vec3_sub(target, rec.p) };
        
        //return vec3_const_mul( color(temp, world, depth - 1, p, rec), 0.5 );
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
    const int max_depth = 50;
    fprintf(stderr, "Entering draw_some_pixels() func\n");

    int num_spheres = 4;

    Vec3 sphere_ground_material_albedo = vec3(0.8, 0.8, 0.0);
    Vec3 sphere_left_material_albedo = vec3(0.8, 0.8, 0.8);
    Vec3 sphere_center_material_albedo = vec3(0.7, 0.3, 0.3);
    Vec3 sphere_right_material_albedo = vec3(0.8, 0.6, 0.2);

    Material sphere_ground_material = {.s = lambertian_scatter, .albedo = sphere_ground_material_albedo};
    Material sphere_left_material = {.s = dielectric_scatter_2, .albedo = sphere_left_material_albedo, .ir = 1.5f};
    Material sphere_center_material = {.s = lambertian_scatter, .albedo = sphere_center_material_albedo};
    Material sphere_right_material = {.s = metal_scatter, .albedo = sphere_right_material_albedo, .fuzz = CLAMP(1.0, 0.0, 1.0)};

    Sphere sphere_center = {
        .center.x = 0.0,
        .center.y = 0.0,
        .center.z = -1.0,
        .radius = 0.5,
        .mat_ptr = &sphere_center_material
    };

    Sphere sphere_left = {
        .center.x = -1.0,
        .center.y = 0.0,
        .center.z = -1.0,
        .radius = 0.5,
        .mat_ptr = &sphere_left_material
    };

    Sphere sphere_right = {
        .center.x = 1.0,
        .center.y = 0.0,
        .center.z = -1.0,
        .radius = 0.5,
        .mat_ptr = &sphere_right_material
    };

    Sphere sphere_ground = {
        .center.x = 0.0,
        .center.y = -100.5,
        .center.z = -1.0,
        .radius = 100.0,
        .mat_ptr = &sphere_ground_material
    };


    HittableList world;
    Sphere *s_list;
    s_list = (Sphere*)malloc(sizeof(Sphere) * num_spheres);
    
    s_list[0] = sphere_ground;
    s_list[1] = sphere_center;
    s_list[2] = sphere_left;
    s_list[3] = sphere_right;

    world.list = s_list;
    world.list_size = num_spheres;

    Camera cam = create_camera();
    debugCamera(cam);

    Vec3 p = vec3(0, 0, 0);
    HitRecord rec = {.normal.x = 0.0, .normal.y = 0.0, .normal.z = 0.0, .p = p};

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
                col = vec3_add(col, color(r, world, max_depth, p, rec));
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
    srand48(time(NULL));
    setvbuf(stdout, 0, _IOLBF, 4096);
    int* data;
    data = (int*)malloc(sizeof(uint32_t) * nx * ny);

    if ( data == NULL ) 
    {
        fprintf(stderr, "Some tragic shit happend while allocating memory\n");
        return EXIT_FAILURE;
    }

    //stbi_flip_vertically_on_write(-1); // flag is non-zero to flip data vertically
    long current_time = get_tick();

    draw_some_pixels(data);

    long delta = get_tick() - current_time;

    fprintf(stderr, "[*] %ld seconds to trace all the rays\n", delta/1000);

    draw_image(data, nx * ny, nx, ny);

    free(data);

    return EXIT_SUCCESS;
}
