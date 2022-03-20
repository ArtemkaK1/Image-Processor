#include "filters.h"
#include "image.h"
#include "parser.h"

#include <iostream>


void printHelp();

int main(int argc, char** argv) {
    Image image(0, 0);

    image.read("/Users/artemiy/CLionProjects/image_processor/examples/example.bmp");
    image.Export("/Users/artemiy/CLionProjects/image_processor/examples/copy.bmp");
    return 0;
}

void printHelp() {
    std::cout << "**********[ HELP ]**********";
}
