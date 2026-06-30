#include <cstddef>
#include <new>
#include <memory>

class Image {
public:
    Image(unsigned int width, unsigned int height) : width_(width), height_(height) {}
    void operator&() const = delete;

private:
    unsigned int width_;
    unsigned int height_;
};

class VectorOfImages {
public:
    ~VectorOfImages() noexcept{ 
        std::destroy_n(GetValidStoragePtr(),numElements_ );
     }

    Image *GetValidStoragePtr() { 
        return reinterpret_cast<Image*>(std::addressof(storage_));
    }

    void EmplaceBack(unsigned int width, unsigned int height) {
        if (numElements_ >= maxSize_) {
            throw std::bad_alloc{};
        }
        
        std::construct_at(GetValidStoragePtr()+numElements_*sizeof(Image), width, height);

        ++numElements_;
    }

private:
    unsigned int numElements_ = 0;
    static const unsigned int maxSize_ = 20;
    alignas(Image) std::byte storage_[maxSize_ * alignof(Image)];
}; 

int main() {
    VectorOfImages x = VectorOfImages();
    x.EmplaceBack(1, 2);
}