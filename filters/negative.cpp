#include "negative.h"

Image Negative::Apply(Image &image) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    for (size_t y = 0; y < result.GetHeight(); ++y) {
        for (size_t x = 0; x < result.GetWidth(); ++x) {
            result.GetColor(x, y).r = 255 - image.GetColor(x, y).r;
            result.GetColor(x, y).g = 255 - image.GetColor(x, y).g;
            result.GetColor(x, y).b = 255 - image.GetColor(x, y).b;
        }
    }
    return result;
}