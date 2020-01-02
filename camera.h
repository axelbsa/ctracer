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

}Camera;


Camera create_camera();
void set_camera_position(Camera *c, Vec3 origin, Vec3 hori, Vec3 vert, Vec3 orig);
Ray get_ray(Camera c, float u, float v);

#endif  /* CAMERA_H */
