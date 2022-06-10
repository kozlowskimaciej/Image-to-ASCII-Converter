#include <stdio.h>
#include <stdlib.h>

#include "include/image.h"

constexpr unsigned int OUTPUT_WIDTH = 50;
constexpr unsigned int OUTPUT_HEIGHT = 25;

int main(void)
{
    Image img("kot.jpg");
    printf("%s", img.toAscii(OUTPUT_WIDTH, OUTPUT_HEIGHT).c_str());
}
