#include<type_traits>
#include<cassert>

template<typename T>
struct IsFloat:std::false_type{};

template<>
struct IsFloat<float>:std::true_type{};


template<typename T>
T calc(T val) {
    if constexpr(IsFloat<T>::value) {
        return val*val;
    } else if constexpr(std::is_arithmetic_v<T>) {
         return val*2;
    } 
        
    return val;
}

int main() {
    assert(calc(7) == 14);
    assert(calc(7.0f) == 49.0f);
    assert(calc("cdscdscd") == "cdscdscd");

    return 0;
}