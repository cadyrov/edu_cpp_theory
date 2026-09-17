#include "counter.h"

#include <memory>

struct Counter::Impl {
    int value = 0;
};

Counter::Counter() : impl_(std::make_unique<Impl>()) {};
Counter::~Counter() = default;

void Counter::increment() {
    impl_.get()->value++;
};

void Counter::reset() {
    impl_.get()->value = 0;
};

int Counter::value() const {
    return impl_.get()->value;
}
