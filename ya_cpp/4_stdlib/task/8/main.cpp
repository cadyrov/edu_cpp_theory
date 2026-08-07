#include <string>
#include <cassert>
#include <initializer_list>
#include <string>
#include <print>

constexpr int getMaxSize(std::initializer_list<std::string> in) {
    int max = 0;

    for (auto& s: in) {
        if (s.size() > max) {
            max = s.size();
        }
    }

    return max;
}


[[nodiscard]] bool isSSO(const std::string &s) {
    const auto objectBegin = reinterpret_cast<std::uintptr_t>(&s);
    const auto objectEnd = objectBegin + sizeof(s);
    const auto data = reinterpret_cast<std::uintptr_t>(s.data());

    return data >= objectBegin && data < objectEnd;
}


int main() {
    assert(getMaxSize({"hello", "s", "ab", "hhh"}) == 5);
    static_assert(getMaxSize({"hello", "s", "ab", "world!"}) == 6);


    const std::string shortString = "sso";
    const std::string longString(100, 'x');

    std::println("isSSO(short) = {}", isSSO(shortString));
    std::println("isSSO(long) = {}", isSSO(longString));

  return 0;
} 