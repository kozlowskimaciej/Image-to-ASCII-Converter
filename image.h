#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image/stb_image.h"

class Image
{
private:
    static constexpr unsigned int MAX_SUM = 765; // 255 * 3 channels (R,G,B)
    int width_, height_, channels_;
    int szanel;
    unsigned char *img;
    double group_brightness(unsigned int group_x, unsigned int group_y, unsigned int group_width, unsigned int group_height) const;
    char select_char(double brightness) const;

public:
    Image(const std::string &filepath);
    int width() const { return width_; };
    int height() const { return height_; };
    int channels() const { return channels_; };
    std::string toAscii(int out_width, int out_height);
};