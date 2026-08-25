#include <utility>
#include <string>

template<typename T>
class Box {
public:
    template<typename U>
    explicit Box(U&& in):val_(std::forward<U>(in)){}

    const T& get() const{
        return val_;
    }

    template<typename U>
    void set(U&& in) {
        val_ = std::forward<U>(in);
    }
private:
    T val_;
};

int main() {
    Box<int> b(42);
    
    Box<std::string> aa("cdslkcnmslkd");
}