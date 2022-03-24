#pragma once

#include "../image.h"

#include <string>

static const std::vector<std::pair<int, int>> STEPS_AROUND = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

class FilterProtocol {
public:
    virtual Image Apply(Image& image, std::vector<std::string> params = {}) {
        return Image(0, 0);
    }
};
