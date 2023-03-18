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


void debug_s_list(HittableList* world)
{
    for (int i = 0; i < world->list_size; i++)
    {
        Sphere sp = world->list[i];
        printf("Material Albedo %f\n", sp.mat_ptr->albedo.y);
    }
}


HittableList random_scene(Sphere *s_list, Material *materials) {
    fprintf(stderr, "ENtering random_scene\n");
    HittableList world;

    int num_spheres = 300;
    int sphere_index = 0;


    //auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));

    /*Material sphere_ground_material = materials[sphere_index];
    sphere_ground_material.s = lambertian_scatter;
    sphere_ground_material.albedo = vec3(0.5f, 0.5f, 0.5f);*/
    Material sphere_ground_material = {.s = lambertian_scatter, .albedo = vec3(0.5f, 0.5f, 0.5f)};
    materials[sphere_index] = sphere_ground_material;

    Sphere sphere_ground = {.center.x = 0.0, .center.y = -1000, .center.z = 0,
                            .radius = 1000.0, .mat_ptr = &materials[sphere_index]};
    s_list[sphere_index++] = sphere_ground;
    //world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            Vec3 center = vec3(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if (length(vec3_sub(center, vec3(4, 0.2, 0))) > 0.9)
            {
                //shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    Vec3 albedo = vec3_mul(vec3_random(), vec3_random());

                    //sphere_material->albedo = albedo;
                    materials[sphere_index].albedo = albedo;

                    //sphere_material->s = lambertian_scatter;
                    materials[sphere_index].s = lambertian_scatter;

                    Sphere sp = {.center = center, .radius = 0.2f, .mat_ptr = &materials[sphere_index]};
                    s_list[sphere_index++] = sp;
                } else if (choose_mat < 0.95) {
                    // metal
                    Vec3 albedo = vec3_random_mm(0.5, 1);
                    double fuzz = random_double_mm(0, 0.5);

                    //sphere_material->albedo = albedo;
                    materials[sphere_index].albedo = albedo;

                    //sphere_material->fuzz = fuzz;
                    materials[sphere_index].fuzz = fuzz;

                    //sphere_material->s = metal_scatter;
                    materials[sphere_index].s = metal_scatter;

                    //world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    Sphere sp = {.center = center, .radius = 0.2f, .mat_ptr = &materials[sphere_index]};
                    s_list[sphere_index++] = sp;
                } else {
                    // glass

                    //sphere_material->ir = 1.5;
                    materials[sphere_index].ir = 1.5;

                    //sphere_material->s = dielectric_scatter_2;
                    materials[sphere_index].s = dielectric_scatter_2;

                    //world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    Sphere sp = {.center = center, .radius = 0.2f, .mat_ptr = &materials[sphere_index]};
                    s_list[sphere_index++] = sp;
                }
            }
        }
    }

    //auto material1 = make_shared<dielectric>(1.5);
    //world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));
    //Material material11 = {.s = dielectric_scatter_2, .ir = 1.5};
    materials[sphere_index].s = dielectric_scatter_2;
    materials[sphere_index].ir = 1.5f;

    Sphere sp11 = {.center = vec3(0, 1, 0), .radius = 1.0f, .mat_ptr = &materials[sphere_index]};
    s_list[sphere_index++] = sp11;

    //auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    //world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));
    //Material material12 = {.s = lambertian_scatter, .albedo = vec3(0.4f, 0.2f, 0.1f)};
    materials[sphere_index].s = lambertian_scatter;
    materials[sphere_index].albedo = vec3(0.4f, 0.2f, 0.1f);

    Sphere sp12 = {.center = vec3(-4, 1, 0), .radius = 1.0f, .mat_ptr = &materials[sphere_index]};
    s_list[sphere_index++] = sp12;

    //auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    //world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
    //Material material13 = {.s = metal_scatter, .albedo = vec3(0.7f, 0.6f, 0.5f), .fuzz = 0.0};
    materials[sphere_index].s = metal_scatter;
    materials[sphere_index].albedo = vec3(0.7f, 0.6f, 0.5f);
    materials[sphere_index].fuzz = 0.0f;

    Sphere sp13 = {.center = vec3(4, 1, 0), .radius = 1.0f, .mat_ptr = &materials[sphere_index]};
    s_list[sphere_index++] = sp13;

    world.list = s_list;
    world.list_size = sphere_index + 1;

    fprintf(stderr, "Finished creating random_scene(), we made %d spheres\n", sphere_index + 1);

    return world;
}


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
    //fprintf(stderr, "Entering draw_some_pixels() func\n");

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
        //fprintf(stderr, "Found hit, checking material pointer scatter function\n");
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
        float t = (unit_direction.y + 1.0f) * 0.5f;
        float distance = (1.0f - t);

        Vec3 identity = {1.0, 1.0, 1.0};
        Vec3 gradiant = {0.5, 0.7, 1.0};

        Vec3 v_distance = vec3_const_mul(identity, distance);
        Vec3 v_gradiant = vec3_const_mul(gradiant, t);
        return vec3_add(v_distance, v_gradiant);
    }
}


void draw_some_pixels(
        int image_width, int image_height,
        int samples_per_pixel, double aspect_ratio, int* data
)
{
    const int max_depth = 50;
    fprintf(stderr, "Entering draw_some_pixels() func\n");

    /*
    int num_spheres = 5;

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

    Sphere sphere_left_2 = {
        .center.x = -1.0,
        .center.y = 0.0,
        .center.z = -1.0,
        .radius = -0.4,
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
    s_list[3] = sphere_left_2;
    s_list[4] = sphere_right;

    world.list = s_list;
    world.list_size = num_spheres;
    */

    fprintf(stderr, "Creating s_list\n");

    Sphere* s_list = 0;
    Material* materials = 0;

    s_list = (Sphere*)malloc(sizeof(Sphere) * 500);
    materials = (Material*)malloc(sizeof(Material) * 500);

    HittableList world = random_scene(s_list, materials);

    //debug_s_list(&world);

    fprintf(stderr, "After creating random_scene\n");

    Vec3 look_from = vec3(13,2,3);
    Vec3 look_at = vec3(0,0,0);
    float dist_to_focus = length(vec3_sub(look_from, look_at));

    Camera cam = create_camera(
            look_from,
            look_at,
            vec3(0,1,0),
            20,
            aspect_ratio,
            0.1,
            10.0
    );

    //Camera cam = create_camera_old(90,aspect_ratio);

    //camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 90, aspect_ratio);
    debugCamera(cam);

    Vec3 p = vec3(0, 0, 0);
    HitRecord rec = {.normal.x = 0.0, .normal.y = 0.0, .normal.z = 0.0, .p = p};

    for (int j = image_height - 1; j >= 0; j--)
    {
        for (int i = 0; i < image_width; i++)
        {
            Vec3 col = vec3(0.0, 0.0, 0.0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                float u = ((float) i + (float)random_double()) / (float) image_width;
                float v = ((float) j + (float)random_double()) / (float) image_height;
                Ray r = get_ray(cam, u, v);
                col = vec3_add(col, color(r, world, max_depth, p, rec));
            }

            col = vec3_const_div(col, samples_per_pixel);
            col = vec3( sqrt(col.x), sqrt(col.y), sqrt(col.z) );

            int ir = (int) (255.99f * col.x);
            int ig = (int) (255.99f * col.y);
            int ib = (int) (255.99f * col.z);

            int index = (j * image_width) + i;
            data[index] = (0xff << 24) | (ib << 16) | (ig << 8) | ir;
        }
        print_progress(j, image_height);
    }
    free(s_list);
    fprintf(stderr, "\nLeaving draw_some_pixels()\n");
}


int main()
{
    srand48(time(NULL));
    setvbuf(stdout, 0, _IOLBF, 4096);

    double aspect_ratio = 3.0f / 2.0f;
    //double aspect_ratio = 2.0 / 1.0;
    const int image_width = 400;
    const int image_height = (int)(image_width / aspect_ratio);
    const int samples_per_pixel = 10;

    int* data;
    data = (int*)malloc(sizeof(uint32_t) * image_width * image_height);

    if ( data == NULL ) 
    {
        fprintf(stderr, "Some tragic shit happend while allocating memory\n");
        return EXIT_FAILURE;
    }

    double current_time = get_time();
    draw_some_pixels(image_width, image_height, samples_per_pixel, aspect_ratio, data);
    double delta = get_time() - current_time;
    fprintf(stderr, "[*] %g seconds to trace all the rays\n", delta);
    //fprintf(stderr, "[*] Done trace all the rays\n");

    draw_image(data, image_width * image_height, image_width, image_height);

    free(data);

    return EXIT_SUCCESS;
}
