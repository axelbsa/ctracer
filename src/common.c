#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vec3.h"

/*
 * drand48 for windows
 * https://gist.github.com/mortennobel/8665258
*/

#include <math.h>

#ifdef _WIN32
#include "windows.h"
#else
#include <sys/time.h>
#endif


#define RAND48_SEED_0   (0x330e)
#define RAND48_SEED_1 (0xabcd)
#define RAND48_SEED_2 (0x1234)
#define RAND48_MULT_0 (0xe66d)
#define RAND48_MULT_1 (0xdeec)
#define RAND48_MULT_2 (0x0005)
#define RAND48_ADD (0x000b)



double get_time()
{
#ifdef _WIN32
    return GetTickCount() / 1000.0;
#else
    struct timeval tv;

	gettimeofday(&tv, 0);

	return tv.tv_sec + tv.tv_usec * 1.0e-6;
#endif

}

unsigned short _rand48_seed[3] = {
        RAND48_SEED_0,
         RAND48_SEED_1,
         RAND48_SEED_2
};
unsigned short _rand48_mult[3] = {
         RAND48_MULT_0,
         RAND48_MULT_1,
         RAND48_MULT_2
 };
unsigned short _rand48_add = RAND48_ADD;

void _dorand48(unsigned short xseed[3])
{
	         unsigned long accu;
	         unsigned short temp[2];
	
	         accu = (unsigned long)_rand48_mult[0] * (unsigned long)xseed[0] +
	          (unsigned long)_rand48_add;
	         temp[0] = (unsigned short)accu;        
	         accu >>= sizeof(unsigned short)* 8;
	         accu += (unsigned long)_rand48_mult[0] * (unsigned long)xseed[1] +
	          (unsigned long)_rand48_mult[1] * (unsigned long)xseed[0];
	         temp[1] = (unsigned short)accu;        
	         accu >>= sizeof(unsigned short)* 8;
	         accu += _rand48_mult[0] * xseed[2] + _rand48_mult[1] * xseed[1] + _rand48_mult[2] * xseed[0];
	         xseed[0] = temp[0];
	         xseed[1] = temp[1];
	         xseed[2] = (unsigned short)accu;
}

double erand48(unsigned short xseed[3])
{
         _dorand48(xseed);
         return ldexp((double) xseed[0], -48) +
                ldexp((double) xseed[1], -32) +
                ldexp((double) xseed[2], -16);
}

double drand48(){
	return erand48(_rand48_seed);
}

void srand48(long seed){
	_rand48_seed[0] = RAND48_SEED_0;
	_rand48_seed[1] = (unsigned short)seed;
	_rand48_seed[2] = (unsigned short)(seed >> 16);
	_rand48_mult[0] = RAND48_MULT_0;
	_rand48_mult[1] = RAND48_MULT_1;
	_rand48_mult[2] = RAND48_MULT_2;
	_rand48_add = RAND48_ADD;
}

double random_double()
{
    //return (double)rand() / (double)((unsigned)RAND_MAX + 1.0);
    return drand48();
}

double random_double_mm(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

Vec3 random_in_unit_sphere()
{
    Vec3 p;

    do 
    {
        p = vec3(random_double(), random_double(), random_double());
        p = vec3_const_mul(p, 1.2);
        p = vec3_sub(p, vec3(1.0, 1.0, 1.0));
    
    } while( square_length(p) >= 1.0 );

    //fprintf(stderr, "Square length < 1.0: %f ", square_length(p));

    return p;
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}


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