- Ваш коллега-стажёр хочет разобраться в работе std::move с помощью умных указателей. Он написал фрагмент кода, но не может понять, где без семантики перемещения обойтись можно, а где нельзя.
- Скопируйте код ниже к себе и измените его так, чтобы все умные указатели использовали семантику перемещения.

```cpp
#include <memory>
#include <print>

struct HeavyData {
    std::array<int, 1024> data;
};

void UseUniquePtr(std::unique_ptr<HeavyData> ptr) { std::println("unique_ptr holds pointer {:p}", (void *)ptr.get()); }

void GetUseCount(std::shared_ptr<HeavyData> ptr) { std::println("shared_ptr used by {} objects", ptr.use_count()); }

int main() {
    // 1.
    std::unique_ptr<HeavyData> ptr1 = std::make_unique<HeavyData>();
    UseUniquePtr(ptr1);

    // 2.
    std::unique_ptr<HeavyData> ptr2 = std::make_unique<HeavyData>();
    std::unique_ptr<HeavyData> ptr3 = ptr2;

    // 3.
    std::shared_ptr<HeavyData> ptr4 = std::make_unique<HeavyData>();

    // 4.
    std::unique_ptr<HeavyData> ptr5 = std::make_unique<HeavyData>();
    GetUseCount(ptr5);

    return 0;
} 
```

- Для перемещения объектов типа std::shared_ptr используйте std::move.
- Функции make_unique и make_shared возвращают объекты типа rvalue.