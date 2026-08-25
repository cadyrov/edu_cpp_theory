#include<cassert>

template<typename Derived>
class Counter {
public:
    inline static unsigned count_ = 0;

public:
    Counter() { ++count_; }
    Counter(const Counter&) { ++count_; }
    Counter(Counter&&) { ++count_; }
    ~Counter() { --count_; }

    static unsigned count() {
        return count_;
    }
};

class Banana: public Counter<Banana> {};
class Apple: public Counter<Apple> {};

int main() {
    Banana x;
    Banana y = x;

    Banana z{};

    Apple xa;
    Apple xb{};

    assert(Banana::count() == 3);
    assert(Apple::count() == 2);



    return 0;
}