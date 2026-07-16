#include<cstdlib>
#include <memory>

class Image {
public:
    Image(unsigned int width, unsigned int height) : width_(width), height_(height) {}
    void operator&() const = delete;

private:
    unsigned int width_;
    unsigned int height_;
};

int main() {
    const std::size_t len = 5;
    Image* arrPtrPN = (Image*)std::malloc(sizeof(Image) * len);

    for (std::size_t i = 0; i < len;++i) {
        new (std::addressof(arrPtrPN[i])) Image(256,256);

        arrPtrPN[i].~Image();
    }

    std::free(arrPtrPN);

    return 0;
}