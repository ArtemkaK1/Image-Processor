#pragma once

#include "filter_protocol.h"

class GaussBlur: public FilterProtocol {
public:

    Image Apply(Image& image, std::vector<std::string> params = {}) override;

    void CreateGaussMatrix();

private:
    int sigma_ = 0;
    int matrix_size_ = 0;
    double matrix_sum_ = 0;
    std::vector<double> gauss_matrix_;
};
