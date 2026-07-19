
template <typename>
class IsPointer{
    public:
    static constexpr bool value = false;
};

int main() {
    static_assert(IsPointer<int>::value == false);

    return 0;
}

