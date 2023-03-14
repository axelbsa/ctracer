#include <math.h>

#include "camera.h"
#include "ray.h"
#include "vec3.h"


Camera create_camera(double vfov, double aspect_ratio)
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


void set_camera_position(Camera *c, Vec3 origin, Vec3 hori, Vec3 vert, Vec3 orig)
{
    c->horizontal = hori;
    c->vertical = vert;
    c->origin = orig;
}


Ray get_ray(Camera c, float u, float v)
{
    Vec3 v_horizontal = vec3_const_mul(c.horizontal, u);
    Vec3 v_vertical = vec3_const_mul(c.vertical, v);

    Vec3 lower_plus_hori = vec3_add(c.lower_left_corner, v_horizontal);
    Vec3 vert_minus_orig = vec3_sub(v_vertical, c.origin);

    Vec3 result = vec3_add(lower_plus_hori, vert_minus_orig);

    Ray look_at = {.A = c.origin, .B = result};

    return look_at;
}
