#include <string_view>

template <typename T>
struct TypeName {
    static constexpr const char* value = "unknown";
};

template <>
struct TypeName<double> {
    static constexpr const char* value = "double";
};

    
int main() {
    static_assert(TypeName<char>::value == std::string_view("unknown"));
    static_assert(TypeName<double>::value == std::string_view("double"));

    return 0;
}