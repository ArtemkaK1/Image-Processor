#include "filters.h"

static const std::vector<std::pair<int, int>> steps_around = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

Image Crop::Apply(Image &image, std::vector<std::string> params) {
    int new_width = std::min(static_cast<int>(std::stoi(params[0])), image.GetWidth()); // TODO
    int new_height = std::min(static_cast<int>(std::stoi(params[1])), image.GetHeight()); // TODO
    Image result = Image(new_width, new_height);
    for (int y = 0; y < result.GetHeight(); ++y) {
        for (int x = 0; x < result.GetWidth(); ++x) {
            result.GetColor(x, y) = image.GetColor(x, y);
        }
    }
    return result;
}

Image GrayscaleFilter::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            auto curr_red = image.GetColor(x, y).r;
            auto curr_green = image.GetColor(x, y).g;
            auto curr_blue = image.GetColor(x, y).b;
            result.GetColor(x, y).r = 0.299f * curr_red + 0.587f * curr_green + 0.114f * curr_blue;
            result.GetColor(x, y).g = 0.299f * curr_red + 0.587f * curr_green + 0.114f * curr_blue;
            result.GetColor(x, y).b = 0.299f * curr_red + 0.587f * curr_green + 0.114f * curr_blue;
        }
    }
    return result;
}

Image Negative::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    for (int y = 0; y < result.GetHeight(); ++y) {
        for (int x = 0; x < result.GetWidth(); ++x) {
            result.GetColor(x, y).r = 255.0f - image.GetColor(x, y).r;
            result.GetColor(x, y).g = 255.0f - image.GetColor(x, y).g;
            result.GetColor(x, y).b = 255.0f - image.GetColor(x, y).b;
        }
    }
    return result;
}

Image Sharpening::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.GetWidth(), image.GetHeight());
    int w = image.GetWidth(), h = image.GetHeight();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int new_red = 0;
            int new_green = 0;
            int new_blue = 0;
            for (auto item : steps_around) {
                int new_x = std::max(0, std::min(h - 1, x + item.first));
                int new_y = std::max(0, std::min(w - 1, y + item.second));
                new_red += (-1) * static_cast<int>(image.GetColor(new_x, new_y).r);
                new_green += (-1) * static_cast<int>(image.GetColor(new_x, new_y).g);
                new_blue += (-1) * static_cast<int>(image.GetColor(new_x, new_y).b);
            }
            new_red += 5 * static_cast<int>(image.GetColor(x, y).r);
            new_green += 5 * static_cast<int>(image.GetColor(x, y).g);
            new_blue += 5 * static_cast<int>(image.GetColor(x, y).b);
            result.GetColor(x, y).r = static_cast<uint8_t>(std::min(255, std::max(0, new_red)));
            result.GetColor(x, y).g = static_cast<uint8_t>(std::min(255, std::max(0, new_green)));
            result.GetColor(x, y).b = static_cast<uint8_t>(std::min(255, std::max(0, new_blue)));
        }
    }
    return result;
}

Image EdgeDetection::Apply(Image &image, std::vector<std::string> params) {
    GrayscaleFilter grayscale;
    Image result = grayscale.Apply(image);

    int threshold = std::stoi(params[0]);

    int w = image.GetWidth(), h = image.GetHeight();
    for (int y = 0; y < h; ++y) {
        for (int x= 0; x < w; ++x) {
            int new_color = 0;
            for (auto item : steps_around) {
                int new_x = std::max(0, std::min(h - 1, x + item.first));
                int new_y = std::max(0, std::min(w - 1, y + item.second));
                new_color += (-1) * static_cast<int>(image.GetColor(new_x, new_y).r);
            }
            new_color += 4 * static_cast<int>(image.GetColor(x, y).r);
            if (new_color > threshold) {
                result.GetColor(x, y).r = 255.0f;
                result.GetColor(x, y).g = 255.0f;
                result.GetColor(x, y).b = 255.0f;
            } else {
                result.GetColor(x, y).r = 0.0f;
                result.GetColor(x, y).g = 0.0f;
                result.GetColor(x, y).b = 0.0f;
            }
        }
    }
    return result;
}
