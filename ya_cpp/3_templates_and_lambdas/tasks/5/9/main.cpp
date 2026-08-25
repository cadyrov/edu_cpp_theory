//9. Напишите `WrapperByInt<C>`, где `C` - шаблон с нетиповым параметром `int`.
#include <vector>

template <template <int> typename C>
class WrapperByInt {
public:
    C<5> a;
};

template <int Val>
struct B {
    static constexpr int val = Val;
};


int main() {

   WrapperByInt<B> b;

   return 0;
}