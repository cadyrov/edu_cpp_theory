//5. Напишите `make_box`, который создает объект `Box<T>` через perfect forwarding.
#include <cassert>
#include <vector>
#include <cstddef>



template<typename T>
class Box{
    public:
        template<typename T1>
        Box(T1&& in):value_(std::forward<T1>(in)){};

        T value_;
};

template<typename T>
auto make_box(T&& in) {
    return  Box<std::decay_t<T>>(std::forward<T>(in));
}

int main() {
    auto a = make_box(3);
    
    return 0;
}
