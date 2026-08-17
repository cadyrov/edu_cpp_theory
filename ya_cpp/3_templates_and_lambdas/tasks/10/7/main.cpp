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