#pragma once

#include "filter_construction.h"

#include <iostream>
#include <string_view>
#include <vector>

class Parser {
public:
    Parser(int argc, char* argv[]);

    std::string_view input_;
    std::string_view output_;
    std::vector<Filter> filters_;
};
