#include <stdlib.h>
#include <stdint.h>


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void draw_image(int* data, uint32_t length, int nx, int ny)
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
    stbi_flip_vertically_on_write(1);
    int val = stbi_write_png("someshit.png", nx, ny, 4, data, 0);

    if (!val) {
        fprintf(stderr, "SOME SHIT FAILED\n");
    } else {
        fprintf(stderr, "stb_write returned %d\n", val);
    }

    /*//int val = stbi_write_bmp("someshit.bmp", WIDTH, HEIGHT, 3, data);*/
    /*val = stbi_write_tga("someshit.tga", nx, ny, 4, data);*/

    /*if (!val) {*/
        /*fprintf(stderr, "SOME SHIT FAILED\n");*/
    /*} else {*/
        /*fprintf(stderr, "stb_write returned %d\n", val);*/
    /*}*/
}
