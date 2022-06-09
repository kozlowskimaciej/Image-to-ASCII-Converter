#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image/stb_image.h"

constexpr unsigned int GROUP_HEIGHT = 60;
constexpr unsigned int GROUP_WIDTH = 30;
constexpr unsigned int MAX_SUM = 765; // 255 * 3 channels (R,G,B)

char select_char(double brightness)
{
    if (brightness < 0.2)
    {
        return ' ';
    }
    else if (brightness < 0.4)
    {
        return '.';
    }
    else if (brightness < 0.6)
    {
        return ':';
    }
    else if (brightness < 0.8)
    {
        return '=';
    }
    else
        return '#';
};

double group_brightness(unsigned int img_width, unsigned char *img)
{
    double pixel_sum = 0;

    for (int i = 0; i < GROUP_WIDTH; ++i)
        for (int j = 0; j < GROUP_HEIGHT; ++j)
            for (unsigned int k = 0; k < 3; ++k) // sum three channels of pixel
                pixel_sum += static_cast<double>(img[3 * (i + j * img_width) + k]);

    return (pixel_sum / (GROUP_HEIGHT * GROUP_WIDTH)) / MAX_SUM;
}

int main(void)
{
    int width, height, channels;
    unsigned char *img = stbi_load("kot.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        throw;
    }

    for (unsigned int row = 0; row < height / GROUP_HEIGHT; ++row)
    {
        // printf("%d %d %d", width, height, channels);
        for (unsigned int clmn = 0; clmn < width / GROUP_WIDTH; ++clmn)
        {

            img += channels * GROUP_WIDTH; // move pointer to the next pixel

            printf("%c", select_char(group_brightness(width, img)));

            // printf("%d", i % width);
        }
        // if ( % width == 0)
        // {
        printf("\n");
        img += channels * width * GROUP_HEIGHT;
        // }
    }
}
