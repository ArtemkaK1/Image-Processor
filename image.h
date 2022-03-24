#pragma once

#include "color.h"

#include <vector>

class Image {
public:
    Image(size_t width, size_t height);

    Color GetColor(size_t x, size_t y) const;
    Color& GetColor(size_t x, size_t y);

    size_t GetWidth() const;
    size_t GetHeight() const;

    void Read(const char* path);

    void Export(const char* path) const;

private:
    size_t width_;
    size_t height_;
    std::vector<Color> colors_;
};
