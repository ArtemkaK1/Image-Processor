#include "crop.h"

Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {}

Image Crop::Apply(Image &image) {
    size_t new_width = std::min(width_, image.GetWidth());
    size_t new_height = std::min(height_, image.GetHeight());
    Image result = Image(new_width, new_height);
    for (size_t y = image.GetHeight() - result.GetHeight(); y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < result.GetWidth(); ++x) {
            result.GetColor(x, y - image.GetHeight() + result.GetHeight()) = image.GetColor(x, y);
        }
    }
    return result;
}
