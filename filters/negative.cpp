#include "negative.h"

Image Negative::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    for (int y = 0; y < result.GetHeight(); ++y) {
        for (int x = 0; x < result.GetWidth(); ++x) {
            result.GetColor(x, y).r = 1.0f - image.GetColor(x, y).r;
            result.GetColor(x, y).g = 1.0f - image.GetColor(x, y).g;
            result.GetColor(x, y).b = 1.0f - image.GetColor(x, y).b;
        }
    }
    return result;
}