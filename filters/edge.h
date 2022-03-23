#pragma once

#include "filter_protocol.h"
#include "grayscale.h"

class EdgeDetection : public GrayscaleFilter {
public:
    Image Apply(Image& image, std::vector<std::string> params = {}) override;
};