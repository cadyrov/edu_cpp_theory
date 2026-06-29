#include <cstdlib>
#include <iostream>
#include <jemalloc.h>
#include <print>

struct HeavyObject {
    int32_t data[1000];
};

// ===== Ваш код здесь =====

static std::size_t numAllocs{0};
static std::size_t numDeallocs{0};

static std::size_t numArrayAllocs{0};
static std::size_t numArrayDeallocs{0};



//
// Функции, не вызывающие утечки памяти
//

void *operator new(std::size_t sz) {
    void *ptr  = malloc(sz); 

    if (ptr == nullptr) {
        throw std::bad_alloc();
    }

    ++numAllocs;

    return ptr;
}

void operator delete(void *ptr) noexcept{
    if (ptr == nullptr) {
        return;
    }

    free(ptr);

    ++numDeallocs;
}
void operator delete(void *ptr, std::size_t sz) noexcept {
    if (ptr == nullptr) {
        return;
    }

    free(ptr);

    ++numDeallocs;
}

void *operator new[](std::size_t sz) {
    void *ptr = malloc(sz); 

    if (ptr == nullptr) {
        throw std::bad_alloc();
    }

    ++numArrayAllocs;

    return ptr;
}

void operator delete[](void *ptr) noexcept {
    if (ptr == nullptr) {
        return;
    }

    free(ptr);

    ++numArrayDeallocs;
}

void operator delete[](void *ptr, std::size_t sz) noexcept {
    if (ptr == nullptr) {
        return;
    }

    free(ptr);

    ++numArrayDeallocs;
}

void ProperArrayManagement() {
    HeavyObject *hoArr = new HeavyObject[5];
    delete[] hoArr;
}

void ProperMemoryManagement() {
    HeavyObject *ho = new HeavyObject;
    delete ho;
}

// =========================

//
// Функции утечки памяти
//
void LeakArrayMemory() { new HeavyObject[10]; }
void LeakSomeMemory() { new HeavyObject{}; }

//
// Функции для теста 2
//
void CatchMeIfYouCanRecursively(unsigned int depth) {
    if (depth <= 0)
        return;

    HeavyObject *obj = new HeavyObject{};

    HeavyObject *temp = new HeavyObject{};

    if (depth % 2 == 0) {
        ProperMemoryManagement();
    }

    if (depth % 3 == 0) {
        LeakSomeMemory();
    }

    if (depth % 7 == 0) {
        ProperArrayManagement();
    }

    if (depth % 11 == 0) {
        LeakArrayMemory();
    }

    CatchMeIfYouCanRecursively(depth - 1);
    delete obj;
}

//
// Функции для теста 1
//
void MemoryLeaksWithFor(HeavyObject *templateObject) {
    HeavyObject *array1 = new HeavyObject[10];

    for (std::size_t sz = 0; sz < 10; ++sz) {
        HeavyObject *array2 = new HeavyObject[10];
        LeakSomeMemory();
        ProperMemoryManagement();
        delete[] array2;
    }

    delete templateObject;
    delete[] array1;
}

void CatchMeIfYouCan() {
    HeavyObject *obj = new HeavyObject{};

    ProperMemoryManagement();

    MemoryLeaksWithFor(obj);
}

int main(int argc, char **argv) {
    // Простая утечка памяти
    for (std::size_t sz = 0; sz < 100; ++sz) {
        LeakSomeMemory();
    }

    // Несколько вложенных функций с циклом
    CatchMeIfYouCan();

    // Несколько вложенных функций с рекурсией
    CatchMeIfYouCanRecursively(42);

    std::print("Number of allocations:   {}\n"
               "Number of deallocations: {}\n"
               "Number of array allocations:   {}\n"
               "Number of array deallocations: {}\n\n"
               "Number of leaks in total: {}\n\n",
               numAllocs, numDeallocs, numArrayAllocs, numArrayDeallocs,
               numAllocs - numDeallocs + numArrayAllocs - numArrayDeallocs);

    std::print("Jemalloc approx. number of leaks:   {}\n", 0);
}