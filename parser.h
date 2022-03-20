#pragma once

#include "filter_construction.h"

#include <iostream>
#include <string_view>
#include <vector>

class Parser {
public:
    Parser(int argc, char* argv[]) {
        try {
            for (int i = 1; i < argc; ++i) {
                if (i == 1) {
                    input_ = argv[i];
                } else if (i == 2) {
                    output_ = argv[i];
                } else {
                    std::string curr_arg = argv[i];
                    if (curr_arg[0] == '-') {
                        filters_.push_back(Filter());
                        filters_[size(filters_) - 1].filterName = curr_arg;
                    } else {
                        filters_[size(filters_) - 1].filterParams.push_back(curr_arg);
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Wrong input" << std::endl;
        }
    }

    std::string_view input_;
    std::string_view output_;
    std::vector<Filter> filters_;
};
