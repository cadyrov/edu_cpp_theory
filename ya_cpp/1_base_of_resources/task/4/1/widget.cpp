#include "widget.h"

#include <memory>
#include <string>
#include <vector>

struct Widget::Impl {
    std::vector<std::string> history_;
};

Widget::Widget() : impl_(std::make_unique<Impl>()) {};
Widget::~Widget() = default;

void Widget::SetTitle(std::string_view title) {
    impl_.get()->history_.push_back(std::string(title));
};

std::string Widget::Title() const {
    if (impl_.get()->history_.empty()) {
        return "";
    }

    return impl_.get()->history_[impl_.get()->history_.size() - 1];
};

void Widget::Print(std::ostream& os) const {
    for (auto it = impl_.get()->history_.rbegin(); it != impl_.get()->history_.rend(); ++it) {
        os << *it << "\n";
    }
};