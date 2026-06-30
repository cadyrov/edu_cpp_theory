#include <memory>

class Image {};

class Box {
public:
    Box() : imageData_(new Image{}) {}
    
    Box(Box& other):imageData_(other.imageData_) {
        other.imageData_ = nullptr;
    }
    Box(Box&& other):imageData_(std::move(other.imageData_)) {}

    Box& operator = (Box& other)  noexcept{
        if (this == &other) {
            return *this;
        }

        delete imageData_;
        imageData_ = other.imageData_;

        other.imageData_ = nullptr;

        return *this;
    }

    Box& operator = (Box&& other) noexcept{
        if (this == &other) {
            return *this;
        }

        delete imageData_;
        this->imageData_ = other.imageData_;
        other.imageData_ = nullptr;

        return *this;
    }

    ~Box() noexcept{delete imageData_;}

private:
    Image *imageData_;
}; 