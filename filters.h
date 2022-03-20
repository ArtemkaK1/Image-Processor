#pragma once

#include "filter_construction.h"
#include "image.h"

class FilterProtocol {
public:
    virtual Image Apply(Image& image, std::vector<std::string> params = {}) {
        return Image(0, 0);
    }
};

class Crop : public FilterProtocol {
public:
    Image Apply(Image& image, std::vector<std::string> params = {}) override;
};

class GrayscaleFilter : public FilterProtocol {
public:
    Image Apply(Image& image, std::vector<std::string> params = {}) override;
};

class Negative : public FilterProtocol {
public:
    Image Apply(Image& image, std::vector<std::string> params = {}) override;
};

class Sharpening : public FilterProtocol {
public:
    Image Apply(Image& image, std::vector<std::string> params = {}) override;
};

class EdgeDetection : public GrayscaleFilter {
public:
    Image Apply(Image& image, std::vector<std::string> params = {}) override;
};


