#include "file_manager/file_manager.h"

#include <iostream>

int main() {
    BMP bmp("example.bmp");
    bmp.write("example_copy.bmp");
    return 0;
}
