#ifndef COMMON_H
#define COMMON_H

#include "vec3.h"

#define MIN(A,B)    ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#define MAX(A,B)    ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })

#define CLAMP(x, low, high) ({\
  __typeof__(x) __x = (x); \
  __typeof__(low) __low = (low);\
  __typeof__(high) __high = (high);\
  __x > __high ? __high : (__x < __low ? __low : __x);\
  })


extern void srand48(long seed);
extern double drand48();

extern double random_double();
extern Vec3 random_in_unit_sphere();
extern Vec3 random_unit_vector();


#endif
