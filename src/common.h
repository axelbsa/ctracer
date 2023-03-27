#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

//#define MIN(A,B)    ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
//#define MAX(A,B)    ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })

#define CLAMP(x, low, high) ({\
  __typeof__(x) __x = (x); \
  __typeof__(low) __low = (low);\
  __typeof__(high) __high = (high);\
  __x > __high ? __high : (__x < __low ? __low : __x);\
  })

static inline void print_progress(int j, int image_height);

void print_progress(int j, int image_height)
{

    int current = (image_height - j) * 100 / image_height;
    fprintf(stderr, "\r");
    fprintf(stderr, "[");

    for (int i = 0; i < current; i++)
    {
        fprintf(stderr, "#");
    }

    for (int i = current; i < 100; i++)
    {
        fprintf(stderr, " ");
    }

    fprintf(stderr, "] %%%d", current);
}


#endif
