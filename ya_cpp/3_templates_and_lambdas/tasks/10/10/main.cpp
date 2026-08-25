template <typename Derived> class Base {
  private:
    Base() = default;
    friend Derived;
};

class Some : public Base<Some> {};
class Wrong : public Base<Some> {};

int main() {
    Some x;

    // Wrong n;

    return 0;
}
