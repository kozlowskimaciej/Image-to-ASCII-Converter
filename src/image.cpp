#include "../include/image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image/stb_image.h"

Image::Image(const std::string &filepath)
    : img_(stbi_load(filepath.c_str(), &width_, &height_, &channels_, 0))
{
    if (img_ == NULL)
    {
        throw;
    }
}

std::string Image::toAscii(int out_width, int out_height)
{
    std::string asciiImg = "";

    const unsigned int group_width = (width_ / out_width) | 1;
    const unsigned int group_height = (height_ / out_height) | 1;

    for (unsigned int row = 0; row < height_ / group_height; ++row)
    {
        for (unsigned int column = 0; column < width_ / group_width; ++column)
        {
            asciiImg += select_char(group_brightness(column, row, group_width, group_height));
        }
        asciiImg += '\n';
    }

    return asciiImg;
}

char Image::select_char(double brightness) const
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

double Image::group_brightness(unsigned int group_x, unsigned int group_y, unsigned int group_width, unsigned int group_height) const
{
    double pixel_sum = 0;
    unsigned int group_offset = channels_ * (group_x * group_width + group_y * group_height * width_); // offset to the beginning of the group (in pixels)

    for (unsigned int row = 0; row < group_height; ++row)
        for (unsigned int col = 0; col < group_width; ++col)
            for (unsigned int k = 0; k < 3; ++k) // sum three channels of pixel
                pixel_sum += static_cast<double>(img_[group_offset + 3 * (col + row * width_) + k]);

    return (pixel_sum / (group_height * group_width)) / MAX_SUM;
}