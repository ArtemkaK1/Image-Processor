#pragma once

#include "../image.h"

#include <string>

class FilterProtocol {
public:
    virtual Image Apply(Image& image) = 0;
    virtual ~FilterProtocol() = default;
};
