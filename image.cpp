#include "image.h"

#include <iostream>
#include <fstream>

const int fileHeaderSize = 14;
const int informationHeaderSize = 40;

Color::Color() : r(0), g(0), b(0) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::~Color() {}

Image::Image(int width, int height) :  width_(width), height_(height), colors_(std::vector<Color>(width * height)) {}

Image::~Image() {}

Color Image::getColor(int x, int y) const {
    return colors_[y * width_ + x];
}

Color& Image::getColor(int x, int y) {
    return colors_[y * width_ + x];
}

void Image::setColor(const Color& color, int x, int y) {
    colors_[y * width_ + x].r = color.r;
    colors_[y * width_ + x].g = color.g;
    colors_[y * width_ + x].b = color.b;
}

int Image::getWidth() const {
    return width_;
}

int Image::getHeight() const {
    return height_;
}

void Image::read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File cannot be opened" << std::endl;
        return;
    }

    uint8_t fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    uint8_t informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
        std::cout << "Not BMP image" << std::endl;
        f.close();
        return;
    }

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);

    width_ = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    height_ = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    colors_.resize(width_ * height_);
    const int paddingAmount = ((4 - (width_ * 3) % 4) % 4);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            uint8_t color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            colors_[y * width_ + x].r = static_cast<float>(color[2]) / 255.0f;
            colors_[y * width_ + x].g = static_cast<float>(color[1]) / 255.0f;
            colors_[y * width_ + x].b = static_cast<float>(color[0]) / 255.0f;
        }
        f.ignore(paddingAmount);
    }
    f.close();

    std::cout << "File can be read" << std::endl;
}

void Image::Export(const char *path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File cannot be opened" << std::endl;
        return;
    }

    uint8_t bmpPad[3] = {0, 0, 0};
    const int paddingAmount = ((4 - (width_ * 3) % 4) % 4);

    const int fileSize = fileHeaderSize + informationHeaderSize + width_ * height_ * 3 + paddingAmount * height_;

    uint8_t fileHeader[fileHeaderSize];

    // Тип файла
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    // Размер файла
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    // Резерв
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    fileHeader[8] = 0;
    fileHeader[9] = 0;

    //Отступ для данных пикселей
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    uint8_t informationHeader[informationHeaderSize];

    // Размер хедера
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Ширина
    informationHeader[4] = width_;
    informationHeader[5] = width_ >> 8;
    informationHeader[6] = width_ >> 16;
    informationHeader[7] = width_ >> 24;

    // Высота
    informationHeader[8] = height_;
    informationHeader[9] = height_ >> 8;
    informationHeader[10] = height_ >> 16;
    informationHeader[11] = height_ >> 24;

    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // Число бит на пиксель
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    // Не используем
    for (size_t i = 16; i < 40; ++i) {
        informationHeader[i] = 0;
    }

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            uint8_t r = static_cast<uint8_t>(getColor(x, y).r * 255.0f);
            uint8_t g = static_cast<uint8_t>(getColor(x, y).g * 255.0f);
            uint8_t b = static_cast<uint8_t>(getColor(x, y).b * 255.0f);

            uint8_t color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    f.close();

    std::cout << "File created" << std::endl;
}
