#pragma once

#include "filter_protocol.h"

class Crop : public FilterProtocol {
public:
    Image Apply(Image& image, std::vector<std::string> params = {}) override;
};
