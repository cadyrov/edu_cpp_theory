#include <utility>

template<typename T>
class Box {
public:
    template<typename U>
    explicit Box(U&& in):val_(std::forward<U>(in)){}
private:
    T val_;
};

int main() {
    Box<int> b(42);
    int a = 10;
    Box<int> aa(a);
}