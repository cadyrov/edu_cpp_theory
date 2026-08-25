//Напишите шаблон `RemovePointer<T>`.
#include <type_traits>

template<typename T>
class RemovePointer{
   public:
   using type = T;
};

template<typename T>
class RemovePointer<T*>{
   public:
   using type = T;
};


int main() {
    static_assert(std::is_same_v<RemovePointer<int>::type, int> );
    static_assert(std::is_same_v<RemovePointer<int*>::type, int> );
    return 0;
}
