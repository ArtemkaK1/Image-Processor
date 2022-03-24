#include "filters/edge.h"
#include "filters/crop.h"
#include "filters/gauss.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharp.h"
#include "image.h"

#include <filesystem>
#include <iostream>
#include <string>

void printHelp();

int main(int argc, char** argv) {
    if (argc == 0) {
        printHelp();
        return 0;
    }

    if (argc < 3) {
        std::cout << "Wrong arguments" << std::endl;
        return 0;
    }

    if(!std::filesystem::exists(argv[1])) {
        std::cout << "File does not exist" << std::endl;
        return 0;
    }

    std::vector<FilterProtocol*> filters;
    for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
        std::string filter = argv[i];
        if (filter == "-crop") {
            filters.push_back(new Crop(std::stoi(argv[i + 1]), std::stoi(argv[i + 2])));
        } else if (filter == "-gs") {
            filters.push_back(new GrayscaleFilter());
        } else if (filter == "-neg") {
            filters.push_back(new Negative());
        } else if (filter == "-sharp") {
            filters.push_back(new Sharpening());
        } else if (filter == "-edge") {
            filters.push_back(new EdgeDetection(std::stoi({argv[i + 1]})));
        } else if (filter == "-blur") {
            filters.push_back(new GaussBlur(std::stoi(argv[i + 1])));
        }
    }

    Image image(0, 0);
    image.Read(argv[1]);

    for (auto item : filters) {
        image = item->Apply(image);
    }

    image.Export(argv[2]);
}

void printHelp() {
    std::cout << "**********[ HELP ]**********";
}
