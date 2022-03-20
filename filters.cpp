#include "filters.h"

Image Crop::Apply(Image &image, std::vector<std::string> params) {
    return FilterProtocol::Apply(image, params);
}

Image GrayscaleFilter::Apply(Image &image, std::vector<std::string> params) {
    return FilterProtocol::Apply(image, params);
}

Image Negative::Apply(Image &image, std::vector<std::string> params) {
    return FilterProtocol::Apply(image, params);
}

Image Sharpening::Apply(Image &image, std::vector<std::string> params) {
    return FilterProtocol::Apply(image, params);
}

Image EdgeDetection::Apply(Image &image, std::vector<std::string> params) {
    return GrayscaleFilter::Apply(image, params);
}
