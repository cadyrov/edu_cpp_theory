#include "widget.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Widget::Impl {
    std::vector<std::string> history_;
};

Widget::Widget() : impl_(std::make_unique<Impl>()) {};
Widget::~Widget() = default;

Widget::Widget(Widget&& other) noexcept : impl_(std::move(other.impl_)) {};
Widget& Widget::operator=(Widget&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    impl_ = std::move(other.impl_);

    return *this;
};

bool Widget::empty() const {
    return impl_ == nullptr;
}

void Widget::SetTitle(std::string_view title) {
    if (impl_ == nullptr) {
        impl_ = std::make_unique<Impl>();
    }

    impl_.get()->history_.push_back(std::string(title));
};

std::string Widget::Title() const {
    if (impl_ == nullptr || impl_.get()->history_.empty()) {
        return "";
    }

    return impl_.get()->history_[impl_.get()->history_.size() - 1];
};

void Widget::Print(std::ostream& os) const {
    if (impl_ == nullptr || impl_.get()->history_.empty()) {
        os << "empty history\n";
        return;
    }

    for (auto it = impl_.get()->history_.rbegin(); it != impl_.get()->history_.rend(); ++it) {
        os << *it << "\n";
    }
};