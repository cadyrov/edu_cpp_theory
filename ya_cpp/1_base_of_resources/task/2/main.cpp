#include <cstdlib>
#include <memory>

int main() {
    const std::size_t size = 10;

    auto pArr = std::make_unique<int[]>(size);
    auto pValue = std::make_unique<double>();

    return 1;
}
