#include "document.h"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct Document::Impl {
    std::vector<std::string> data_;
};

Document::Document() : impl_(std::make_unique<Impl>()) {};
Document::~Document() = default;

Document::Document(const Document& other) {
    impl_ = std::make_unique<Impl>();
    if (other.impl_ == nullptr) {
        return;
    }

    impl_.get()->data_ = other.impl_.get()->data_;
};

Document& Document::operator=(const Document& other) {
    if (this == &other) {
        return *this;
    }

    Document cp(other);

    impl_ = std::move(cp.impl_);

    return *this;
};

Document::Document(Document&& other) {
    impl_ = std::move(other.impl_);
};

Document& Document::operator=(Document&& other) {
    if (this == &other) {
        return *this;
    }

    Document cp(std::move(other));

    impl_ = std::move(cp.impl_);

    return *this;
};

void Document::AddLine(const std::string& line) {
    if (impl_ == nullptr) {
        impl_ = std::make_unique<Impl>();
    }

    impl_->data_.push_back(line);
}

const std::string& Document::operator[](size_t n) const {
    if (impl_ == nullptr || impl_->data_.size() <= n) {
        throw std::runtime_error("wrong index");
    }

    return impl_->data_[n];
};

size_t Document::size() const {
    if (impl_ == nullptr) {
        return 0;
    }

    return impl_->data_.size();
};

std::ostream& operator<<(std::ostream& os, const Document& doc) {
    if (doc.impl_ == nullptr) {
        return os;
    }

    for (auto& line : doc.impl_->data_) {
        os << line << "\n";
    }

    return os;
};
