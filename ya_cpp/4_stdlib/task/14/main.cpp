#include <array>
#include <print>
#include <set>
#include <string>
#include <string_view>
#include <print>
#include <compare>

struct Id {
    int part1, part2, part3;
    auto operator <=>(const Id& value) const = default;
};

struct HeavyObject {
    std::array<int, 128> data{};
    Id id;
    std::string name;

    auto operator <=>(const HeavyObject& value) const {
        if (name != value.name) {
            return name <=>value.name;
        }

        return id <=>value.id;
    };

    auto operator <=>(std::string_view val) const {
        return name <=> val;
    };
};

int main() {
    std::set<HeavyObject, std::less<>> objects{
        HeavyObject{{},{1, 2, 3}, "CPU_Param"},
        HeavyObject{{},{4, 5, 6}, "GPU_Param"},
        HeavyObject{{},{7, 8, 9}, "CPU_Param"},
    };

    if (objects.contains(HeavyObject{{},{7, 8, 9}, "CPU_Param"})) {
        std::println("Found element with id ID(7, 8, 9)");
    }

    std::println("Has element with name=CPU_Param: {}", objects.contains(HeavyObject{{},{0, 0, 0},  "CPU_Param"}));

    std::println("Num of elements with name=GPU_Param: {}", objects.count(HeavyObject{{},{0, 0, 0}, "GPU_Param"}));
} 