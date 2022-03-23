#include "edge.h"

Image EdgeDetection::Apply(Image &image, std::vector<std::string> params) {
    GrayscaleFilter grayscale;
    Image result = grayscale.Apply(image);

    int threshold = std::stoi(params[0]);

    int w = image.GetWidth(), h = image.GetHeight();
    for (int y = 0; y < h; ++y) {
        for (int x= 0; x < w; ++x) {
            int new_color = 0;
            for (auto item : STEPS_AROUND) {
                int new_x = std::max(0, std::min(h - 1, x + item.first));
                int new_y = std::max(0, std::min(w - 1, y + item.second));
                new_color += (-1) * static_cast<int>(image.GetColor(new_x, new_y).r);
            }
            new_color += 4 * static_cast<int>(image.GetColor(x, y).r);
            if (new_color > threshold) {
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