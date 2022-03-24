#include "edge.h"

EdgeDetection::EdgeDetection(int threshold) : threshold_(threshold) {}

Image EdgeDetection::Apply(Image &image) {
    GrayscaleFilter grayscale;
    Image result = grayscale.Apply(image);
    std::vector<std::pair<int, int>> steps_around = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    size_t w = image.GetWidth(), h = image.GetHeight();
    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            int new_color = 0;
            for (auto [step_x, step_y] : steps_around) {
                int new_x = std::clamp(static_cast<int>(x + step_x), 0, static_cast<int>(h - 1));;
                int new_y = std::clamp(static_cast<int>(y + step_y), 0, static_cast<int>(w - 1));
                new_color += (-1) * static_cast<int>(image.GetColor(new_x, new_y).r);
            }
            new_color += 4 * static_cast<int>(image.GetColor(x, y).r);
            if (new_color > threshold_) {
                result.GetColor(x, y).r = 255;
                result.GetColor(x, y).g = 255;
                result.GetColor(x, y).b = 255;
            } else {
                result.GetColor(x, y).r = 0;
                result.GetColor(x, y).g = 0;
                result.GetColor(x, y).b = 0;
            }
        }
    }
    return result;
}
