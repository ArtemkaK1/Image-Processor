#include "grayscale.h"

Image GrayscaleFilter::Apply(Image &image) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            auto curr_red = image.GetColor(x, y).r;
            auto curr_green = image.GetColor(x, y).g;
            auto curr_blue = image.GetColor(x, y).b;
            double gray_color = 0.299 * curr_red + 0.587 * curr_green + 0.114 * curr_blue;
            result.GetColor(x, y).r = static_cast<int>(gray_color);
            result.GetColor(x, y).g = static_cast<int>(gray_color);
            result.GetColor(x, y).b = static_cast<int>(gray_color);
        }
    }
    return result;
}