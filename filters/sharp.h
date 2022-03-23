#pragma once

#include "filter_protocol.h"


class Sharpening : public FilterProtocol {
public:
    Image Apply(Image& image, std::vector<std::string> params = {}) override;
};