#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"


typedef struct CameraClass
{

    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lens_radius;

}Camera;


Camera create_camera(
        Vec3 look_from,
        Vec3 look_at,
        Vec3 vup,
        double vfov,
        double aspect_ratio,
        double aperture,
        double focus_dist
);

void set_camera_position(Camera *c, Vec3 origin, Vec3 hori, Vec3 vert, Vec3 orig);
Ray get_ray(Camera c, float s, float t);

#endif  /* CAMERA_H */
