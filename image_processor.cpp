#include "filters/edge.h"
#include "filters/crop.h"
#include "filters/gauss.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharp.h"
#include "image.h"
#include "parser.h"

#include <iostream>


void printHelp();

int main(int argc, char** argv) {
    Image image1(0, 0);
    Image image2(0, 0);
    Image image3(0, 0);
    Image image4(0, 0);
    Image image5(0, 0);

    GrayscaleFilter grayscaleFilter;
    image1.read("/Users/artemiy/CLionProjects/image_processor/examples/example.bmp");
    image1 = grayscaleFilter.Apply(image1);
    image1.Export("/Users/artemiy/CLionProjects/image_processor/examples/copy1.bmp");

    Negative negative;
    image2.read("/Users/artemiy/CLionProjects/image_processor/examples/example.bmp");
    image2 = negative.Apply(image2);
    image2.Export("/Users/artemiy/CLionProjects/image_processor/examples/copy2.bmp");

    Crop crop;
    image3.read("/Users/artemiy/CLionProjects/image_processor/examples/example.bmp");
    image3 = crop.Apply(image3, {"1000", "1000"});
    image3.Export("/Users/artemiy/CLionProjects/image_processor/examples/copy3.bmp");

    Sharpening sharpening;
    image4.read("/Users/artemiy/CLionProjects/image_processor/examples/example.bmp");
    image4 = sharpening.Apply(image4);
    image4.Export("/Users/artemiy/CLionProjects/image_processor/examples/copy4.bmp");

    EdgeDetection edgeDetection;
    image5.read("/Users/artemiy/CLionProjects/image_processor/examples/example.bmp");
    image5 = edgeDetection.Apply(image5, {"4"});
    image5.Export("/Users/artemiy/CLionProjects/image_processor/examples/copy5.bmp");
    return 0;
}

void printHelp() {
    std::cout << "**********[ HELP ]**********";
}
