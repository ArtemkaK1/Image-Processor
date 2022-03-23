#include "sharp.h"

#include <iostream>

Image Sharpening::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    int w = image.GetWidth(), h = image.GetHeight();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int new_red = 0;
            int new_green = 0;
            int new_blue = 0;
            for (auto item : STEPS_AROUND) {
                int new_x = std::max(0, std::min(h - 1, x + item.first));
                int new_y = std::max(0, std::min(w - 1, y + item.second));
                new_red += (-1) * image.GetColor(new_x, new_y).r;
                new_green += (-1) * image.GetColor(new_x, new_y).g;
                new_blue += (-1) * image.GetColor(new_x, new_y).b;

            }
            new_red += 5 * image.GetColor(x, y).r;
            new_green += 5 * image.GetColor(x, y).g;
            new_blue += 5 * image.GetColor(x, y).b;


            result.GetColor(x, y).r = static_cast<uint8_t>(std::clamp(new_red, 0, 255));
            result.GetColor(x, y).g = static_cast<uint8_t>(std::clamp(new_green, 0, 255));
            result.GetColor(x, y).b = static_cast<uint8_t>(std::clamp(new_blue, 0, 255));
        }
    }
    return result;
}