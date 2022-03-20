#pragma once

#include <vector>

struct Color {
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image {
public:
    Image(int width, int height);
    ~Image();

    Color getColor(int x, int y) const;
    void setColor(const Color&, int x, int y);

    void read(const char* path);

    void Export(const char* path) const;

private:
    int width_;
    int height_;
    std::vector<Color> colors_;
};
