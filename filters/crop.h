#pragma once

#include "filter_protocol.h"

class Crop : public FilterProtocol {
public:
    Crop(size_t width, size_t height);
    Image Apply(Image& image) override;
private:
    size_t width_;
    size_t height_;
};
