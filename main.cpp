#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image/stb_image.h"
constexpr unsigned int OUTPUT_WIDTH = 100;
constexpr unsigned int OUTPUT_HEIGHT = 50;
constexpr unsigned int MAX_SUM = 765; // 255 * 3 channels (R,G,B)

char select_char(double brightness)
{

    if (brightness < 0.1)
        return ' ';
    if (brightness < 0.2)
        return ':';
    if (brightness < 0.3)
        return '*';
    if (brightness < 0.4)
        return 'o';
    if (brightness < 0.5)
        return '&';
    if (brightness < 0.6)
        return '*';
    if (brightness < 0.8)
        return '@';

    return '#';
};

double group_brightness(unsigned int group_x, unsigned int group_y, unsigned int img_width, unsigned char *img, unsigned int group_width, unsigned int group_height)
{
    double pixel_sum = 0;
    unsigned int group_offset = 3 * (group_x * group_width + group_y * group_height * img_width); // offset to the beginning of the group (in pixels)

    for (int row = 0; row < group_height; ++row)
        for (int clmn = 0; clmn < group_width; ++clmn)
            for (unsigned int k = 0; k < 3; ++k) // sum three channels of pixel
                pixel_sum += static_cast<double>(img[group_offset + 3 * (clmn + row * img_width) + k]);

    return (pixel_sum / (group_height * group_width)) / MAX_SUM;
}

int main(void)
{
    int width, height, channels;
    unsigned char *const img = stbi_load("kot.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        throw;
    }

    const unsigned int GROUP_WIDTH = width / OUTPUT_WIDTH;
    const unsigned int GROUP_HEIGHT = height / OUTPUT_HEIGHT;

    for (unsigned int row = 0; row < height / GROUP_HEIGHT; ++row)
    {
        // printf("%d %d %d", width, height, channels);
        for (unsigned int column = 0; column < width / GROUP_WIDTH; ++column)
        {

            // img += channels * GROUP_WIDTH; // move pointer to the next pixel

            printf("%c", select_char(group_brightness(column, row, width, img, GROUP_WIDTH, GROUP_HEIGHT)));

            // printf("%d", i % width);
        }
        // if ( % width == 0)
        // {
        printf("\n");
        // img += channels * width * GROUP_HEIGHT;
        // }
    }
}
