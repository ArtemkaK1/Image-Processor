#include "filters/edge.h"
#include "filters/crop.h"
#include "filters/gauss.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharp.h"
#include "image.h"
#include "parser.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

void printHelp();

int main(int argc, char** argv) {


    if (argc < 3) {
        std::cout << "Wrong arguments" << std::endl;
        return 0;
    }

    if(!std::filesystem::exists(argv[1])) {
        std::cout << "File does not exist" << std::endl;
        return 0;
    }

    Image image(0, 0);
    image.read(argv[1]);

    for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
        std::string filter = argv[i];
        if (filter == "-crop") {
            Crop crop;
            image = crop.Apply(image, {argv[i + 1], argv[i + 2]});
        } else if (filter == "-gs") {
            GrayscaleFilter grayscaleFilter;
            image = grayscaleFilter.Apply(image);
        } else if (filter == "-neg") {
            Negative negative;
            image = negative.Apply(image);
        } else if (filter == "-sharp") {
            Sharpening sharpening;
            image = sharpening.Apply(image);
        } else if (filter == "-edge") {
            EdgeDetection edge;
            image = edge.Apply(image, {argv[i + 1]});
        } else if (filter == "-blur") {
            GaussBlur blur;
            image = blur.Apply(image, {argv[i + 1]});
        }
    }
    image.Export(argv[2]);
}

void printHelp() {
    std::cout << "**********[ HELP ]**********";
}
