//9. Напишите `Threshold<T, value>` для проверки значения относительно порога.
#include <cassert>
template<typename T, T trh>
class Threshold {
    public:
        static constexpr bool check(const T& in){
            return in < trh; 
        }
};


int main() {
    
    static_assert(Threshold<int, 3>::check(1));
    static_assert(!Threshold<int, 3>::check(5));
    
    return 0;
}
