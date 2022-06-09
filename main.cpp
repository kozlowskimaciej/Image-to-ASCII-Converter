#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image/stb_image.h"

char select_char(double brightness){
    if(brightness < 0.2){
        return ' ';
    }
    else if(brightness < 0.4){
        return '.';
    }
    else if(brightness < 0.6){
        return ':';
    }
    else if(brightness < 0.8){
        return '=';
    }
    else return '#';
};

int main(void) {
    int width, height, channels;
    unsigned char *img = stbi_load("test.jpg", &width, &height, &channels, 0);
    if(img==NULL) {
        throw;
    }

    const int max_sum = 765; // 255 * 3 channels (R,G,B)

    // printf("%d %d %d", width, height, channels);
    for (int i = 0; i < width * height; ++i)
    {
        unsigned int pixel_sum = 0;

        for(int j = 0; j < 3; ++j) // sum three channels of pixel
            pixel_sum += img[j];

        img += channels; // move pointer to the next pixel

        double brightness = static_cast<double>(pixel_sum) / max_sum;

        if (i % width == 0)
            printf("\n");

        printf("%c", select_char(brightness));

        // printf("%d", i % width);
    }
}
