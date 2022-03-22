#include "image.h"

#include <fstream>
#include <iostream>


namespace {
    const int FILE_HEADER_SIZE = 14;
    const int INFORMATION_HEADER_SIZE = 40;
}

Image::Image(int width, int height) :  width_(width), height_(height), colors_(std::vector<Color>(width * height)) {}

Color Image::GetColor(int x, int y) const {
    return colors_[y * width_ + x];
}

Color& Image::GetColor(int x, int y) {
    return colors_[y * width_ + x];
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

void Image::read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File cannot be opened" << std::endl;
        return;
    }

    uint8_t file_header[FILE_HEADER_SIZE];
    f.read(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);

    uint8_t information_header[INFORMATION_HEADER_SIZE];
    f.read(reinterpret_cast<char*>(information_header), INFORMATION_HEADER_SIZE);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        std::cout << "Not BMP image" << std::endl;
        f.close();
        return;
    }

    int file_size = file_header[2] + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);

    width_ = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) + (information_header[7] << 24);
    height_ = information_header[8] + (information_header[9] << 8) + (information_header[10] << 16) + (information_header[11] << 24);

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

    uint8_t bmp_pad[3] = {0, 0, 0};
    const int padding_amount = ((4 - (width_ * 3) % 4) % 4);

    const int file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + width_ * height_ * 3 + padding_amount * height_;

    uint8_t file_header[FILE_HEADER_SIZE];

    // Тип файла
    file_header[0] = 'B';
    file_header[1] = 'M';

    // Размер файла
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;

    // Резерв
    file_header[6] = 0;
    file_header[7] = 0;
    file_header[8] = 0;
    file_header[9] = 0;

    //Отступ для данных пикселей
    file_header[10] = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    uint8_t information_header[INFORMATION_HEADER_SIZE];

    // Размер хедера
    information_header[0] = INFORMATION_HEADER_SIZE;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;

    // Ширина
    information_header[4] = width_;
    information_header[5] = width_ >> 8;
    information_header[6] = width_ >> 16;
    information_header[7] = width_ >> 24;

    // Высота
    information_header[8] = height_;
    information_header[9] = height_ >> 8;
    information_header[10] = height_ >> 16;
    information_header[11] = height_ >> 24;

    information_header[12] = 1;
    information_header[13] = 0;

    // Число бит на пиксель
    information_header[14] = 24;
    information_header[15] = 0;

    // Не используем
    for (size_t i = 16; i < 40; ++i) {
        information_header[i] = 0;
    }

    f.write(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);
    f.write(reinterpret_cast<char*>(information_header), INFORMATION_HEADER_SIZE);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            uint8_t r = static_cast<uint8_t>(GetColor(x, y).r * 255.0f);
            uint8_t g = static_cast<uint8_t>(GetColor(x, y).g * 255.0f);
            uint8_t b = static_cast<uint8_t>(GetColor(x, y).b * 255.0f);

            uint8_t color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmp_pad), padding_amount);
    }

    f.close();

    std::cout << "File created" << std::endl;
}
