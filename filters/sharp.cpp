#include "sharp.h"

Image Sharpening::Apply(Image &image) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    std::vector<std::pair<int, int>> steps_around = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    size_t w = image.GetWidth(), h = image.GetHeight();
    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            int new_red = 0;
            int new_green = 0;
            int new_blue = 0;
            for (auto [step_x, step_y] : steps_around) {
                int new_x = std::clamp(static_cast<int>(x + step_x), 0, static_cast<int>(h - 1));;
                int new_y = std::clamp(static_cast<int>(y + step_y), 0, static_cast<int>(w - 1));
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