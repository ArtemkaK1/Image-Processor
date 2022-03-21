#include "filters.h"

static const std::vector<std::pair<int, int>> steps_around = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

Image Crop::Apply(Image &image, std::vector<std::string> params) {
    int new_width = std::min(static_cast<int>(std::stoi(params[0])), image.getWidth()); // TODO
    int new_height = std::min(static_cast<int>(std::stoi(params[1])), image.getHeight()); // TODO
    Image result = Image(new_width, new_height);
    for (int y = 0; y < result.getHeight(); ++y) {
        for (int x = 0; x < result.getWidth(); ++x) {
            result.getColor(x, y) = image.getColor(x, y);
        }
    }
    return result;
}

Image GrayscaleFilter::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.getWidth(), image.getHeight());
    for (int y = 0; y < image.getHeight(); ++y) {
        for (int x = 0; x < image.getWidth(); ++x) {
            auto curr_red = image.getColor(x, y).r;
            auto curr_green = image.getColor(x, y).g;
            auto curr_blue = image.getColor(x, y).b;
            result.getColor(x, y).r = 0.299f * curr_red + 0.587f * curr_green + 0.114f * curr_blue;
            result.getColor(x, y).g = 0.299f * curr_red + 0.587f * curr_green + 0.114f * curr_blue;
            result.getColor(x, y).b = 0.299f * curr_red + 0.587f * curr_green + 0.114f * curr_blue;
        }
    }
    return result;
}

Image Negative::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.getWidth(), image.getHeight());
    for (int y = 0; y < result.getHeight(); ++y) {
        for (int x = 0; x < result.getWidth(); ++x) {
            result.getColor(x, y).r = 255.0f - image.getColor(x, y).r;
            result.getColor(x, y).g = 255.0f - image.getColor(x, y).g;
            result.getColor(x, y).b = 255.0f - image.getColor(x, y).b;
        }
    }
    return result;
}

Image Sharpening::Apply(Image &image, std::vector<std::string> params) {
    Image result = Image(image.getWidth(), image.getHeight());
    int w = image.getWidth(), h = image.getHeight();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int new_red = 0;
            int new_green = 0;
            int new_blue = 0;
            for (auto item : steps_around) {
                int new_x = std::max(0, std::min(h - 1, x + item.first));
                int new_y = std::max(0, std::min(w - 1, y + item.second));
                new_red += (-1) * static_cast<int>(image.getColor(new_x, new_y).r);
                new_green += (-1) * static_cast<int>(image.getColor(new_x, new_y).g);
                new_blue += (-1) * static_cast<int>(image.getColor(new_x, new_y).b);
            }
            new_red += 5 * static_cast<int>(image.getColor(x, y).r);
            new_green += 5 * static_cast<int>(image.getColor(x, y).g);
            new_blue += 5 * static_cast<int>(image.getColor(x, y).b);
            result.getColor(x, y).r = static_cast<uint8_t>(std::min(255, std::max(0, new_red)));
            result.getColor(x, y).g = static_cast<uint8_t>(std::min(255, std::max(0, new_green)));
            result.getColor(x, y).b = static_cast<uint8_t>(std::min(255, std::max(0, new_blue)));
        }
    }
    return result;
}

Image EdgeDetection::Apply(Image &image, std::vector<std::string> params) {
    GrayscaleFilter grayscale;
    Image result = grayscale.Apply(image);

    int threshold = std::stoi(params[0]);

    int w = image.getWidth(), h = image.getHeight();
    for (int y = 0; y < h; ++y) {
        for (int x= 0; x < w; ++x) {
            int new_color = 0;
            for (auto item : steps_around) {
                int new_x = std::max(0, std::min(h - 1, x + item.first));
                int new_y = std::max(0, std::min(w - 1, y + item.second));
                new_color += (-1) * static_cast<int>(image.getColor(new_x, new_y).r);
            }
            new_color += 4 * static_cast<int>(image.getColor(x, y).r);
            if (new_color > threshold) {
                result.getColor(x, y).r = 255.0f;
                result.getColor(x, y).g = 255.0f;
                result.getColor(x, y).b = 255.0f;
            } else {
                result.getColor(x, y).r = 0.0f;
                result.getColor(x, y).g = 0.0f;
                result.getColor(x, y).b = 0.0f;
            }
        }
    }
    return result;
}
