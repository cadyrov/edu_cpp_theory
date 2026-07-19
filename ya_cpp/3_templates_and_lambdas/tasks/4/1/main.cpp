#include <string_view>

template <typename T>
struct TypeName {
    static constexpr const char* value = "unknown";
};

    
int main() {
    static_assert(TypeName<int>::value == std::string_view("unknown"));

    return 0;
}