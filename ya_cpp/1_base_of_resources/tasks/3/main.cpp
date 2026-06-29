#include "image_encoder.cpp"
#include <iostream>

int main() {

    ImageEncoder ie;

    std::cout << "Format: " << ie.GetFormat() << std::endl;
    std::cout << "Quality: " << ie.GetQuality() << std::endl;

    return 0;
}