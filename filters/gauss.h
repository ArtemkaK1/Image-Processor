#pragma once

#include "filter_protocol.h"

class GaussBlur: public FilterProtocol {
public:
    explicit GaussBlur(int sigma);
    Image Apply(Image& image) override;
    void CreateGaussMatrix();
private:
    int sigma_ = 0;
    size_t matrix_size_ = 0;
    double matrix_sum_ = 0;
    std::vector<double> gauss_matrix_;
};
