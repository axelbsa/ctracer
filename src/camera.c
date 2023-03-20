#include <math.h>

#include "camera.h"
#include "ray.h"
#include "vec3.h"

Camera create_camera_old(double vfov, double aspect_ratio)
{
    Camera c;

    double theta = degrees_to_radians(vfov);
    double h = tan(theta/2);
    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    double focal_length = 1.0;

    c.horizontal        = vec3(viewport_width, 0.0, 0.0);
    c.vertical          = vec3(0.0, viewport_height, 0.0);
    c.origin            = vec3(0.0, 0.0, 0.0);

    Vec3 half_horizonal = vec3_const_div(c.horizontal, 2);
    Vec3 half_vertical  = vec3_const_div(c.vertical, 2);
    Vec3 focal_length_vec = vec3(0.0f, 0.0f, focal_length);

    Vec3 _temp = vec3_sub(c.origin, half_horizonal);
    _temp = vec3_sub(_temp, half_vertical);
    _temp = vec3_sub(_temp, focal_length_vec);

    c.lower_left_corner = _temp;

    return c;
}


Camera create_camera(
        Vec3 look_from, Vec3 look_at, Vec3 vup,
        double vfov, double aspect_ratio, double aperture,
        double focus_dist, double time0, double time1)

{
    Camera c;

    double theta = degrees_to_radians(vfov);
    double h = tan(theta/2);
    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    c.time0 = time0;
    c.time1 = time1;

    //double focal_length = 1.0;   // Is this not used anymore, where did it go?

    c.w = unit_vector(vec3_sub(look_from, look_at));
    c.u = unit_vector( cross(vup, c.w) );
    c.v = cross(c.w, c.u);


    Vec3 horizontal_mul = vec3_const_mul(
            vec3_const_mul(c.u, viewport_width),
            focus_dist
    );

    Vec3 vertical_mul = vec3_const_mul(
            vec3_const_mul(c.v, viewport_height),
            focus_dist
    );

    c.origin            = look_from;
    c.horizontal        = horizontal_mul;
    c.vertical          = vertical_mul;

    Vec3 half_horizontal = vec3_const_div(c.horizontal, 2);
    Vec3 half_vertical   = vec3_const_div(c.vertical, 2);
    Vec3 focus_dist_w    = vec3_const_mul(c.w, focus_dist);

    Vec3 _temp = vec3_sub(c.origin, half_horizontal);
    _temp = vec3_sub(_temp, half_vertical);
    _temp = vec3_sub(_temp, focus_dist_w);

    c.lower_left_corner = _temp;
    c.lens_radius = aperture / 2;

    return c;
}


void set_camera_position(Camera *c, Vec3 origin, Vec3 hori, Vec3 vert, Vec3 orig)
{
    c->horizontal = hori;
    c->vertical = vert;
    c->origin = orig;
}




Ray get_ray_old(Camera c, float u, float v)
{
    Vec3 v_horizontal = vec3_const_mul(c.horizontal, u);
    Vec3 v_vertical = vec3_const_mul(c.vertical, v);

    Vec3 lower_plus_hori = vec3_add(c.lower_left_corner, v_horizontal);
    Vec3 vert_minus_orig = vec3_sub(v_vertical, c.origin);

    Vec3 result = vec3_add(lower_plus_hori, vert_minus_orig);

    Ray look_at = {.A = c.origin, .B = result};

    return look_at;
}


Ray get_ray(Camera c, float s, float t)
{
    //vec3 rd = lens_radius * random_in_unit_disk();
    Vec3 rd = vec3_const_mul(random_in_unit_disc(), c.lens_radius);

    //vec3 offset = u * rd.x() + v * rd.y();
    Vec3 offset_x = vec3_const_mul(c.u, rd.x);
    Vec3 offset_y = vec3_const_mul(c.v, rd.y);

    Vec3 offset = vec3_add(offset_x, offset_y);

    //ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
    Vec3 v_horizontal = vec3_const_mul(c.horizontal, s);
    Vec3 v_vertical = vec3_const_mul(c.vertical, t);
    Vec3 lower_plus_hori = vec3_add(c.lower_left_corner, v_horizontal);
    Vec3 vert_minus_orig = vec3_sub(v_vertical, c.origin);
    vert_minus_orig = vec3_sub(vert_minus_orig, offset);

    Vec3 result = vec3_add(lower_plus_hori, vert_minus_orig);
    Vec3 origin_offset = vec3_add(c.origin, offset);

    Ray look_at = {.A = origin_offset, .B = result, .time = random_double_mm(c.time0, c.time1)};

    return look_at;
}
