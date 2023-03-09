
#include "camera.h"
#include "ray.h"
#include "vec3.h"


Camera create_camera()
{
    Camera c;

    c.lower_left_corner = vec3(-2.0, -1.0, -1.0);
    c.horizontal        = vec3(4.0, 0.0, 0.0);
    c.vertical          = vec3(0.0, 2.0, 0.0);
    c.origin            = vec3(0.0, 0.0, 0.0);
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
