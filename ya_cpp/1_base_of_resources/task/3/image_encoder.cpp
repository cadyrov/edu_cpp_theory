#include "image_encoder.hpp"
#include "chrono"
#include "thread"

class ImageEncoder::Impl{
    public:
        void Encode() noexcept {std::this_thread::sleep_for(std::chrono::seconds(1));};
        std::string GetFormat() const noexcept {return "PNG";};
        int GetQuality() const noexcept {return 42;};
};

ImageEncoder::ImageEncoder():impl_(std::make_unique<Impl>()) {};
ImageEncoder::~ImageEncoder() = default;

void ImageEncoder::Encode() noexcept{ impl_->Encode(); }
std::string ImageEncoder::GetFormat() const noexcept { return impl_->GetFormat(); }
int ImageEncoder::GetQuality() const noexcept { return impl_->GetQuality(); } 