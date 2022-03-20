#include "image.h"

#include <iostream>

int main() {
    Image image(0, 0);

    image.read("/Users/artemiy/CLionProjects/image_processor/examples/example.bmp");
    image.Export("/Users/artemiy/CLionProjects/image_processor/examples/copy.bmp");
    return 0;
}
