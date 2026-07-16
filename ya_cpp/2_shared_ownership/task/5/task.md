Ваш друг, начинающий программист, решил разработать аналог std::vector без использования классов. 

Он создал функции allocate и push_back для выделения памяти под массив и добавление элементов в конец массива соответственно. 
Покажите другу, как использовать умные указатели с классами-обёртками std::out_ptr и std::inout_ptr для безопасной работы с функциями allocate и push_back.

Скопируйте код ниже и перепишите код функции main так, чтобы в нём использовались std::unique_ptr, std::out_ptr и std::inout_ptr.

```cpp
#include <cstring>
#include <iostream>

void allocate(int **arr, unsigned int &capacity, unsigned int desired_capacity) {
    if (desired_capacity <= capacity) {
        return;
    }

    unsigned int new_capacity = (capacity == 0) ? 1 : capacity * 2;
    int *new_arr = new int[new_capacity];

    // Копируем старые данные
    if (*arr) {
        std::memcpy(new_arr, *arr, capacity * sizeof(int));
        delete[] *arr;  // Освобождаем старую память
    }

    *arr = new_arr;
    capacity = new_capacity;
}

void push_back(int **arr, unsigned int &size, unsigned int &capacity, int val) {
    if (size >= capacity) {
        allocate(arr, capacity, capacity * 2);
    }
    (*arr)[size++] = val;
}

int main() {
    int *myArray = nullptr;
    unsigned int size = 0;
    unsigned int capacity = 0;

    allocate(&myArray, capacity, 2);

    push_back(&myArray, size, capacity, 10);
    push_back(&myArray, size, capacity, 20);
    push_back(&myArray, size, capacity, 30);
    push_back(&myArray, size, capacity, 40);

    // Вывод массива
    for (int i = 0; i < size; ++i) {
        std::print("{} ", myArray[i]);
    }

    delete[] myArray;  // Освобождаем память
    return 0;
}
```

- Используйте std::unique_ptr<int[]> для типа массива.
- Используйте std::out_ptr, если функция только создаёт объект.
- Используйте std::inout_ptr, если функция может модифицировать объект.