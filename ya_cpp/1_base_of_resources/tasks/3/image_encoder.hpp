#pragma once

#include "memory"
#include <experimental/propagate_const>
#include "string"

class ImageEncoder {
    public:
        ImageEncoder();
        ImageEncoder(const ImageEncoder&) = delete;   
        ImageEncoder& operator= (const ImageEncoder&) = delete;  
        ~ImageEncoder();

        void Encode() noexcept;
        std::string GetFormat() const noexcept;
        int GetQuality() const noexcept;
    private:
        class Impl;
        std::experimental::propagate_const<std::unique_ptr<Impl>> impl_;
};


