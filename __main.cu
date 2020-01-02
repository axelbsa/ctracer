#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cuda.h"
#include "cuda_runtime_api.h"
#include "cuda_runtime.h"


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define nx 200
#define ny 100


__global__ void add(float a, float b) {}

void draw_image(int* data, uint32_t length)
{
    fprintf(stderr, "Entering draw_image func\n");
    /*
    for (uint32_t i = 0; i < length; i++)
    {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
        data[i] = (0xff << 24) | (r << 16) | (g << 8) | b;
        //printf("RGB = (%02x) (%02x) (%02x) data=%08x\n", r, g, b, data[i]);
    }
    */

    //int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
    int val = stbi_write_png("someshit.png", nx, ny, 4, data, 0);

    if (!val) {
        fprintf(stderr, "SOME SHIT FAILED\n");
    } else {
        fprintf(stderr, "stb_write returned %d\n", val);
    }

    //int val = stbi_write_bmp("someshit.bmp", WIDTH, HEIGHT, 3, data);
    val = stbi_write_tga("someshit.tga", nx, ny, 4, data);

    if (!val) {
        fprintf(stderr, "SOME SHIT FAILED\n");
    } else {
        fprintf(stderr, "stb_write returned %d\n", val);
    }
}

void draw_some_pixels(int* data)
{
    fprintf(stderr, "Entering draw_some_pixels() func\n");

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float r = (float)i / (float)nx;
            float g = (float)j / (float)ny;
            float b = 0.2f;

            int ir = 255.99 * (float)r;
            int ig = 255.99 * (float)g;
            int ib = 255.99 * (float)b;
            int index = (j * nx) + i;
            //fprintf(stderr, "[(i)=%d, (j)=%d   Index = %03d]   ", j, i, index);
            data[index] = (0xff << 24) | (ib << 16) | (ig << 8) | ir;
        }
        add<<<1,1>>>(3.0f, 3.0f);
        //fprintf(stderr, "\n");
    }

    fprintf(stderr, "Leaving draw_some_pixels()\n");
}


int main()
{
    setvbuf(stdout, 0, _IOLBF, 4096);
    int c = int(43);
    int* data;
    data = (int*)malloc(sizeof(uint32_t) * nx * ny);

    if ( data == NULL ) 
    {
        fprintf(stderr, "Some tragic shit happend while allocating memory\n");
        return EXIT_FAILURE;
    }

    //stbi_flip_vertically_on_write(-1); // flag is non-zero to flip data vertically

    draw_some_pixels(data);
    draw_image(data, nx * ny);

    free(data);

    return EXIT_SUCCESS;
}
