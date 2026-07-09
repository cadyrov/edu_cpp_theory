#include <memory>
#include <thread>

std::shared_ptr<int> current;

void reader() {
    auto local = current;
    if (local) {
        (void)*local;
    }
}

void writer() {
    current = std::make_shared<int>(42);
}