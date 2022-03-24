#pragma once

#include "filter_protocol.h"
#include "grayscale.h"

class EdgeDetection : public GrayscaleFilter {
public:
    explicit EdgeDetection(int threshold);
    Image Apply(Image& image) override;
private:
    int threshold_;
};