#include "grayscale.h"

Image GrayscaleFilter::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            auto curr_red = image.GetColor(x, y).r;
            auto curr_green = image.GetColor(x, y).g;
            auto curr_blue = image.GetColor(x, y).b;
            float gray_color = 0.299f * curr_red + 0.587f * curr_green + 0.114f * curr_blue;
            result.GetColor(x, y).r = gray_color;
            result.GetColor(x, y).g = gray_color;
            result.GetColor(x, y).b = gray_color;
        }
    }
    return result;
}