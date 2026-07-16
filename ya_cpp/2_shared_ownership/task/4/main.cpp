#include <memory>
#include <print>

struct HeavyData {
    std::array<int, 1024> data;
};

void UseUniquePtr(std::unique_ptr<HeavyData> ptr) { std::println("unique_ptr holds pointer {:p}", (void *)ptr.get()); }

void GetUseCount(std::shared_ptr<HeavyData> ptr) { std::println("shared_ptr used by {} objects", ptr.use_count()); }

int main() {
    // 1.
    std::unique_ptr<HeavyData> ptr1 = std::make_unique<HeavyData>();
    UseUniquePtr(std::move(ptr1));

    // 2.
    std::unique_ptr<HeavyData> ptr2 = std::make_unique<HeavyData>();
    std::unique_ptr<HeavyData> ptr3 = std::move(ptr2);

    // 3.
    std::shared_ptr<HeavyData> ptr4 = std::make_unique<HeavyData>();

    // 4.
    GetUseCount(std::make_unique<HeavyData>());

    return 0;
} 