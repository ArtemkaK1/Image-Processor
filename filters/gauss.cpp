#include "gauss.h"

#include <cmath>

void GaussBlur::CreateGaussMatrix() {
    matrix_size_ = 6 * sigma_ + 1;
    matrix_size_ = (matrix_size_ % 2 == 0) ? matrix_size_ + 1 : matrix_size_;
    gauss_matrix_.resize(matrix_size_);
    size_t mid = matrix_size_ / 2;
    for (size_t i = 0; i < matrix_size_; ++i) {
        gauss_matrix_[i] = std::pow(M_E, static_cast<double>( -(i - mid) * (i - mid)) / (2 * sigma_ * sigma_)) /
                           std::sqrt(2 * M_PI * sigma_ * sigma_);
        matrix_sum_ += gauss_matrix_[i];
    }
}

GaussBlur::GaussBlur(int sigma) : sigma_(sigma) {
    CreateGaussMatrix();
}

Image GaussBlur::Apply(Image &image) {
    Image img_copy = image;
    size_t mid = matrix_size_ / 2;
    for (size_t i = 0; i < img_copy.GetHeight(); ++i) {
        for (size_t j = 0; j < img_copy.GetWidth(); ++j) {
            double red_sum = 0;
            double green_sum = 0;
            double blue_sum = 0;
            for (size_t k = 0; k < gauss_matrix_.size(); ++k) {
                int x = std::clamp(static_cast<int>(i + k) - static_cast<int>(mid),
                                   0, static_cast<int>(img_copy.GetHeight()) - 1);
                red_sum += static_cast<double>(img_copy.GetColor(x, j).r) / 255 * gauss_matrix_[k];
                green_sum += static_cast<double>(img_copy.GetColor(x, j).g) / 255 * gauss_matrix_[k];
                blue_sum += static_cast<double>(img_copy.GetColor(x, j).b) / 255 * gauss_matrix_[k];
            }
            red_sum /= matrix_sum_;
            green_sum /= matrix_sum_;
            blue_sum /= matrix_sum_;
            image.GetColor(i, j).r = static_cast<uint8_t>(red_sum * 255.0);
            image.GetColor(i, j).g = static_cast<uint8_t>(green_sum * 255.0);
            image.GetColor(i, j).b = static_cast<uint8_t>(blue_sum * 255.0);
        }
    }
    img_copy = image;
    for (size_t i = 0; i < img_copy.GetHeight(); ++i) {
        for (size_t j = 0; j < img_copy.GetWidth(); ++j) {
            double red_sum = 0;
            double green_sum = 0;
            double blue_sum = 0;
            for (size_t k = 0; k < gauss_matrix_.size(); ++k) {
                int y = std::clamp(static_cast<int>(j + k) - static_cast<int>(mid),
                                   0, static_cast<int>(img_copy.GetWidth()) - 1);
                red_sum += static_cast<double>(img_copy.GetColor(i, y).r) / 255 * gauss_matrix_[k];
                green_sum += static_cast<double>(img_copy.GetColor(i, y).g) / 255 * gauss_matrix_[k];
                blue_sum += static_cast<double>(img_copy.GetColor(i, y).b) / 255 * gauss_matrix_[k];
            }
            red_sum /= matrix_sum_;
            green_sum /= matrix_sum_;
            blue_sum /= matrix_sum_;
            image.GetColor(i, j).r = static_cast<uint8_t>(red_sum * 255.0);
            image.GetColor(i, j).g = static_cast<uint8_t>(green_sum * 255.0);
            image.GetColor(i, j).b = static_cast<uint8_t>(blue_sum * 255.0);
        }
    }

    return image;
}
