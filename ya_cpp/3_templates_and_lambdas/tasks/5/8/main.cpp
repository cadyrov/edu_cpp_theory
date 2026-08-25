//8. Напишите шаблон `Wrapper<Container>`, где `Container` - шаблон с одним типовым параметром.
#include <vector>

template <template <typename> typename Container>
class Wrapper {
    public:
    Container<int> data_;
};



int main() {
    Wrapper<std::vector> a;
    
    return 0;
}