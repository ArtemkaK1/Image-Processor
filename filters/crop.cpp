#include "crop.h"

Image Crop::Apply(Image &image, std::vector<std::string> params) {
    int new_width = std::min(static_cast<int>(std::stoi(params[0])), image.GetWidth());
    int new_height = std::min(static_cast<int>(std::stoi(params[1])), image.GetHeight());
    Image result = Image(new_width, new_height);
    for (int y = 0; y < result.GetHeight(); ++y) {
        for (int x = 0; x < result.GetWidth(); ++x) {
            result.GetColor(x, y) = image.GetColor(x, y);
        }
    }
    return result;
}
