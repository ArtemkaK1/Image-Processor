#pragma once

#include "filter_protocol.h"

class Negative : public FilterProtocol {
public:
    Image Apply(Image& image) override;
};