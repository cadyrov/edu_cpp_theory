template <typename T>
class IsPointer{
    public:
    static constexpr bool value = false;
};

template <typename T>
class IsPointer<T*>{
    public:
    static constexpr bool value = true;
};

int main() {
    static_assert(IsPointer<int*>::value);

    return 0;
}

