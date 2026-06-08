#include <cstring>
#include <iostream>
#include <utility>

class Buffer {
    char* data_ = nullptr;
    std::size_t size_ = 0;

public:
    explicit Buffer(std::size_t size)
        : data_(new char[size]), size_(size) {
        std::memset(data_, 0, size_);
    }

    ~Buffer() {
        delete[] data_;
    }

    Buffer(const Buffer& other)
        : data_(new char[other.size_]), size_(other.size_) {
        std::memcpy(data_, other.data_, size_);
    }

    Buffer& operator=(const Buffer& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data_;
        data_ = new char[other.size_];
        size_ = other.size_;
        std::memcpy(data_, other.data_, size_);
        return *this;
    }

    Buffer(Buffer&& other) noexcept
        : data_(other.data_), size_(other.size_) {

    }

    Buffer& operator=(Buffer&& other) noexcept {
        size_ = other.size_;
        delete[] data_;

        data_ = std::move(other.data_);

        return *this;
    }

    std::size_t size() const {
        return size_;
    }
};