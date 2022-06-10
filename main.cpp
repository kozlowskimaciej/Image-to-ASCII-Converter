#include <stdio.h>
#include <stdlib.h>

#include "image.h"

constexpr unsigned int OUTPUT_WIDTH = 15;
constexpr unsigned int OUTPUT_HEIGHT = 15;

int main(void)
{
    Image img("kot.jpg");
    printf("%s", img.toAscii(15, 15).c_str());
}
