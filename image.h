#pragma once

#include "color.h"

#include <vector>

class Image {
public:
    Image(int width, int height);

    Color GetColor(int x, int y) const;
    Color& GetColor(int x, int y);

    int GetWidth() const;
    int GetHeight() const;

    void read(const char* path);

    void Export(const char* path) const;

private:
    int width_;
    int height_;
    std::vector<Color> colors_;
};
